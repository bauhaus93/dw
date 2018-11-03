import os
import logging
import collections
import tempfile

import cv2 as cv
import numpy as np

import texture_generation
from utility import generate_textures, generate_sprites, process_sprites

logger = logging.getLogger()

MaterialPrototype = collections.namedtuple("MaterialPrototpye", ["type", "row", "path"])
Block = collections.namedtuple("Block", ["type", "column", "tex_gen_func", "model_path", "material_paths", "angle_ids", "affix"])


def collect_material_prototypes(atlas_node, resource_dir):
    material_protoypes = {}
    for attr in [child.attrib for child in atlas_node.findall("material_prototype")]:
        mat_prot = MaterialPrototype(
            type = attr["type"],
            row = attr["row"],
            path = os.path.join(resource_dir, attr["path"]))
        material_protoypes[mat_prot.type] = mat_prot
    for (_mat_name, mat_prot) in material_protoypes.items():
        if not os.path.exists(mat_prot.path):
            raise FileNotFoundError(mat_prot.path)
    return material_protoypes

def collect_block_info(block_node, resource_dir, material_protoypes):
    block_type = block_node.attrib["type"]
    logger.debug("Block type: '" + block_type + "'")

    column = int(block_node.attrib["column"])

    texture_gen_function_name = block_node.attrib["texture_gen_function"]
    logger.debug("Texture gen function: '" + texture_gen_function_name + "'")
    try:
        texture_gen_function = getattr(texture_generation, texture_gen_function_name)
    except AttributeError:
        raise AttributeError("Texture generation function not found '" + texture_gen_function_name + "'. It must be exported in __init__ of texture_generation.")
    model_path = os.path.join(resource_dir, block_node.attrib["model_path"])
    logger.debug("Model path: '" + model_path + "'")
    if not os.path.isfile(model_path):
        raise FileNotFoundError(model_path)

    materials = [mat_node.attrib["type"] for mat_node in block_node.findall("material")]
    logger.debug("Materials: " +  " ".join(materials))
    material_paths = [mat_prot.path for (mat_name, mat_prot) in material_protoypes.items() if mat_name in materials]

    angle_ids = [int(cam_node.attrib["angle_id"]) for cam_node in block_node.findall("camera")]
    logger.debug("Camera angle ids: " +  " ".join(str(angle_id) for angle_id in angle_ids))

    return Block(
        type = block_type,
        column = column,
        tex_gen_func = texture_gen_function,
        model_path = model_path,
        material_paths = material_paths,
        angle_ids = angle_ids,
        affix = block_type.lower() + "_"
    )

def create_atlas(atlas_node, resource_dir, render_script_path):
    TMP_DIR = tempfile.gettempdir()

    if not os.path.isfile(render_script_path):
        raise FileNotFoundError(render_script_path)

    logger.info("Collecting material prototypes")
    material_protoypes = collect_material_prototypes(atlas_node, resource_dir)
    logger.info("Collected materials: " + " ".join(material_protoypes))

    logger.info("Parsing blocks")
    for block_node in atlas_node.findall("block"):
        logger.debug("Collecting block info")
        block = collect_block_info(block_node, resource_dir, material_protoypes)
        logger.debug("Collected block info")

        texture_paths = generate_textures(
            block.material_paths,
            block.tex_gen_func,
            TMP_DIR,
            block.affix)
    
        sprite_paths_list = generate_sprites(
            model_path = block.model_path,
            texture_paths = texture_paths,
            camera_angles = block.angle_ids,
            script_path = render_script_path,
            output_dir = TMP_DIR,
        )
        processed_sprite_paths_list = process_sprites(
            sprite_paths_list,
            TMP_DIR,
        )


def create_atlas_old(atlas_node, render_script_path): 
    for block_type in block_types:
        logger.info("Generating '" + block_type + "' sprites")
        model_path = os.path.join(model_dir, block_type + ".blend")
        if not os.path.isfile(model_path):
            logger.error("Model not existing: '" + model_path + "'")
            return False
        sprites_list = generate_sprites(
            material_paths,
            model_path,
            render_script_path,
            block_type,
            "sprite_" + block_type + "_"
        )
        for (index, material_sprites) in enumerate(sprites_list):
            if not index in sprite_map:
                sprite_map[index] = material_sprites
            else:
                sprite_map[index] += material_sprites
        logger.info("Generated '" + block_type + "' sprites")
    _create_atlas(sprite_map, result_path)
    return True


def _create_atlas(sprite_paths_map, output_path):
    logger.info("Creating sprite atlas")
    max_coord = (max(k for (k, v) in sprite_paths_map.items()),
                 max(len(v) for (k, v) in sprite_paths_map.items()))

    sprite_map = {}
    sprite_shape = None
    for mat_index, sprite_list in sprite_paths_map.items():
        for (type_index, sprite_path) in enumerate(sprite_list):
            index_coord = (type_index, mat_index)
            logger.debug("Index: " + str(index_coord) + ", sprite: '" + sprite_path + "'")
            sprite_map[index_coord] = cv.imread(sprite_path, cv.IMREAD_UNCHANGED)
            if sprite_shape == None:
                sprite_shape = sprite_map[index_coord].shape
            elif sprite_map[index_coord].shape != sprite_shape:
                logger.error("Sprite '" + sprite_path + "' has different shape, expected: " + str(sprite_shape) + ", got: " + str(sprite_map[index_coord].shape))
                exit(1)
    atlas_shape = (sprite_shape[0] * (max_coord[0] + 1),
                  sprite_shape[1] * (max_coord[1] + 1),
                  sprite_shape[2])
 
    atlas = np.zeros(atlas_shape)
    logger.info("Creating atlas of shape " + str(atlas.shape))

    for index_coord, sprite in sprite_map.items():
        coord = (index_coord[0] * sprite_shape[1],
                 index_coord[1] * sprite_shape[0])
        atlas[coord[1]:coord[1] + sprite_shape[0], coord[0]:coord[0] + sprite_shape[1]] = sprite
    logger.info("Added " + str(len(sprite_map)) + " sprites to atlas")

    cv.imwrite(output_path, atlas)
    logger.info("Created sprite atlas '" + output_path + "'")