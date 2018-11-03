import os
import subprocess
import tempfile
import logging
import time

from process_image import process_image
from texture_generation.cube_texture import create_cube_texture
from texture_generation.slope_texture import create_slope_texture
from texture_generation.floor_texture import create_floor_texture

logger = logging.getLogger()

def setup_logger():
    FORMAT = r"[%(asctime)-15s] %(levelname)s - %(message)s"
    DATE_FORMAT = r"%Y-%m-%d %H:%M:%S"
    logging.basicConfig(level = logging.DEBUG, format = FORMAT, datefmt = DATE_FORMAT)

def get_files_from_dir(directory, extension = None):
    paths = []
    for file_name in os.listdir(directory):
        file_path = os.path.join(directory, file_name)
        if os.path.isfile(file_path):
            if extension is None or file_name.split(".")[1] == extension:
                paths.append(file_path)
    return paths

def generate_textures(material_paths, create_texture_function, output_dir, output_affix):
    logger.info("Creating textures")
    texture_paths = []
    for mat_path in material_paths:
        file_name, file_ext = os.path.basename(mat_path).split(".")
        output_path = os.path.join(output_dir, output_affix + file_name + "_texture." + file_ext)
        create_texture_function(mat_path, output_path)
        texture_paths.append(output_path)
        logger.debug("Created sprite '" + output_path + "'")
    return texture_paths

def generate_sprites(model_path, texture_paths, camera_angles, script_path, output_dir):
    logger.info("Creating sprites")
    logger.info("Used model: '" + model_path + "'")
    logger.info("Used script: '" + script_path + "'")
    logger.debug("Using " + str(len(texture_paths)) + " textures")
    cmd = [ "blender",
            model_path,
            "--background",
            "--python",
            script_path,
            "--",
            "--output-dir", output_dir,
            "--camera-angles", *[str(a) for a in camera_angles],
            "--texture-paths", *texture_paths]
    logger.info("Starting Blender")
    logger.debug("Invoking command '" + " ".join(cmd) + "'")
    
    try:
        start_time = time.perf_counter()
        cmd_proc = subprocess.Popen(
            cmd,
            stdout = subprocess.PIPE,
            stderr = subprocess.PIPE
        )
        out, err = cmd_proc.communicate()
        out_str = out.decode("ISO-8859-1").split("\n")
        err_str = err.decode("ISO-8859-1").split("\n")

        for line in out_str:
            if len(line) > 1:
                logger.debug("Blender stdout: " + line)
        for line in err_str:
            if len(line) > 1:
                logger.error("Blender stderr: " + line)

        logger.info("Blender finished in {:.2f}s".format(time.perf_counter() - start_time))
    except subprocess.CalledProcessError as ex:
        logger.error("CalledProcessError: " + str(ex))
        exit(1)
    except ex:
        logger.error("Unhandled error: " + str(ex))
        exit(1)

    sprite_paths_list = []
    for texture_path in texture_paths:
        name, ext = os.path.basename(texture_path).split(".")
        if name.endswith("_texture"):
            name = name[:-8]
        directory = os.path.dirname(texture_path)
        paths = []
        for angle in camera_angles:
            sprite_path = os.path.join(directory, name + str(angle) + "." + ext)
            if not os.path.exists(sprite_path):
                logger.warn("Could not find '" + os.path.basename(sprite_path) + "', which should have been generated")
            else:
                paths.append(sprite_path)
                logger.debug("Created sprite '" + sprite_path + "'")
        sprite_paths_list.append(paths)
    return sprite_paths_list

def process_sprites(sprite_paths_list, output_dir):
    logger.info("Processing sprites")
    processed_sprite_paths_list = []
    for sprite_paths in sprite_paths_list:
        processed_paths = []
        for sprite_path in sprite_paths:
            sprite_name = os.path.basename(sprite_path)
            output_path = os.path.join(output_dir, sprite_name)
            process_image(sprite_path, output_path)
            processed_paths.append(output_path)
            logger.debug("Processed sprite '" + sprite_name + "'")
        processed_sprite_paths_list.append(processed_paths)
    return processed_sprite_paths_list