import os
import logging
import collections
import tempfile

import cv2 as cv
import numpy as np

import texture_generation
from build_error import BuildError
from utility import generate_textures, generate_sprites, process_sprites

logger = logging.getLogger()

Atlas = collections.namedtuple("Atlas", ["path", "element_width"])
MaterialPrototype = collections.namedtuple("MaterialPrototype", ["type", "row", "path"])
CameraAngle = collections.namedtuple("CameraAngle", ["id", "column"])
Block = collections.namedtuple("Block", ["type", "tex_gen_func", "model_path", "material_prototypes", "camera_angles", "affix"])

def create_atlas(atlas_node, resource_dir, output_dir, render_script_path):
    TMP_DIR = tempfile.gettempdir()

    if not os.path.isfile(render_script_path):
        raise BuildError("Render script not found: '" + render_script_path + "'")

    atlas = parse_atlas_node(atlas_node, output_dir)

    logger.info("Collecting material prototypes")
    material_protoypes = collect_material_prototypes(atlas_node, resource_dir)
    logger.info("Collected materials: " + " ".join(material_protoypes))

    logger.info("Parsing blocks")
    sprite_path_map = {}
    for block_node in atlas_node.findall("block"):
        logger.debug("Collecting block info")
        block = collect_block_info(block_node, resource_dir, material_protoypes)
        logger.debug("Collected block info")

        sprite_paths_list = create_block_sprites(block, atlas.element_width, TMP_DIR, render_script_path)

        for (i, sprite_paths) in enumerate(sprite_paths_list):
            row = block.material_prototypes[i].row
            for (angle, sprite_path) in zip(block.camera_angles, sprite_paths):
                column = angle.column
                sprite_path_map[(row, column)] = sprite_path

    sprite_map = create_sprite_map(sprite_path_map)
    logger.info("Sprite map contains " + str(len(sprite_map)) + " sprites")

    build_atlas(sprite_map, atlas.path)
    logger.info("Created sprite atlas '" + atlas.path + "'")


def build_atlas(sprite_map, atlas_path):
    sprite_shape = get_sprite_shape(sprite_map)
    logger.info("Shape of atlas elements: " + str(sprite_shape))

    grid_size = get_grid_size(sprite_map)
    logger.info("Atlas grid: " + str(grid_size[0]) + "x" + str(grid_size[1]))

    atlas_shape = (sprite_shape[0] * (grid_size[0]),
                   sprite_shape[1] * (grid_size[1]),
                   sprite_shape[2])
 
    atlas = np.zeros(atlas_shape)
    logger.info("Shape of atlas: " + str(atlas.shape))

    for ((row, col), sprite) in sprite_map.items():
        row_pix = row * sprite_shape[0]
        col_pix = col * sprite_shape[1]
        atlas[row_pix:row_pix + sprite_shape[0], col_pix:col_pix + sprite_shape[1]] = sprite

    cv.imwrite(atlas_path, atlas)

def create_sprite_map(sprite_path_map):
    sprite_map = {}
    for ((row, col), sprite_path) in sprite_path_map.items():
        sprite_map[(row, col)] = cv.imread(sprite_path, cv.IMREAD_UNCHANGED)
    return sprite_map

def get_sprite_shape(sprite_map):
    sprite_shape = None
    for ((row, col), _sprite) in sprite_map.items():
        if sprite_shape is None:
            sprite_shape = sprite_map[(row, col)].shape
        elif sprite_map[(row, col)].shape != sprite_shape:
            raise BuildError("Sprite at " + str(row, col) + " has different shape, expected: " + str(sprite_shape) + ", got: " + str(sprite_map[(row, col)].shape))
    return sprite_shape

def get_grid_size(sprite_map):
    max_row = 0
    max_col = 0
    for ((row, col), _sprite) in sprite_map.items():
        if row > max_row:
            max_row = row
        if col > max_col:
            max_col = col
    return (max_row + 1, max_col + 1)


def parse_atlas_node(atlas_node, output_dir):
    return Atlas(
        path = os.path.join(output_dir, atlas_node.attrib["output_name"]),
        element_width = int(atlas_node.attrib["element_width"])
    )


def parse_camera_node(cam_node):
    return CameraAngle(
         id = int(cam_node.attrib["angle_id"]),
         column = int(cam_node.attrib["column"])
    )

def parse_material_prototype_node(mat_prot_node, resource_dir):
    return MaterialPrototype(
        type = mat_prot_node.attrib["type"],
        row = int(mat_prot_node.attrib["row"]),
        path = os.path.join(resource_dir, mat_prot_node.attrib["path"])
    )

def collect_material_prototypes(atlas_node, resource_dir):
    material_protoypes = {}
    for mat_prot_node in atlas_node.findall("material_prototype"):
        mat_prot = parse_material_prototype_node(mat_prot_node, resource_dir)
        material_protoypes[mat_prot.type] = mat_prot
    for (_mat_name, mat_prot) in material_protoypes.items():
        if not os.path.exists(mat_prot.path):
            raise BuildError("Material prototype path not found: '" + mat_prot.path + "'")
    return material_protoypes

def collect_block_info(block_node, resource_dir, material_prototypes):
    block_type = block_node.attrib["type"]
    logger.debug("Block type: '" + block_type + "'")

    texture_gen_function_name = block_node.attrib["texture_gen_function"]
    logger.debug("Texture gen function: '" + texture_gen_function_name + "'")
    try:
        texture_gen_function = getattr(texture_generation, texture_gen_function_name)
    except AttributeError:
        raise BuildError("Texture generation function not found '" + texture_gen_function_name + "'. It must be exported in __init__ of texture_generation.")
    model_path = os.path.join(resource_dir, block_node.attrib["model_path"])
    logger.debug("Model path: '" + model_path + "'")
    if not os.path.isfile(model_path):
        raise BuildError("Model path not found: '" + model_path + "'")

    materials = [mat_node.attrib["type"] for mat_node in block_node.findall("material")]
    logger.debug("Materials: " +  " ".join(materials))
    block_material_prototypes = [mat_prot for (mat_name, mat_prot) in material_prototypes.items() if mat_name in materials]

    angles = [parse_camera_node(cam_node) for cam_node in block_node.findall("camera")]
    logger.debug("Camera angle ids: " +  " ".join(str(angle.id) for angle in angles))

    return Block(
        type = block_type,
        tex_gen_func = texture_gen_function,
        model_path = model_path,
        material_prototypes = block_material_prototypes,
        camera_angles = angles,
        affix = block_type.lower() + "_"
    )

def create_block_sprites(block, sprite_width, output_dir, render_script_path):
        texture_paths = generate_textures(
            [m.path for m in  block.material_prototypes],
            block.tex_gen_func,
            output_dir,
            block.affix
        )
    
        sprite_paths_list = generate_sprites(
            model_path = block.model_path,
            texture_paths = texture_paths,
            camera_angles = [angle.id for angle in block.camera_angles],
            script_path = render_script_path,
            output_dir = output_dir,
        )

        processed_sprite_paths_list = process_sprites(
            sprite_paths_list,
            sprite_width,
            output_dir,
        )
        return processed_sprite_paths_list