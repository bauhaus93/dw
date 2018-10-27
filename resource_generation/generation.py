import os
import subprocess
import tempfile
import logging
import time

from result_processing.process_image import process_image
from texture_generation.cube_texture import create_cube_texture
from texture_generation.slope_texture import create_slope_texture

logger = logging.getLogger()

def generate_sprites(image_paths, model_path, script_path, texture_type, result_dir, sprite_suffix):
    tmp_dir = tempfile.gettempdir()

    if texture_type == "cube":
        creation_function = create_cube_texture
    elif texture_type == "slope":
        creation_function = create_slope_texture
    else:
        logger.error("Generation of textures for type '" + texture_type + "' is not possible!")
        exit(1)

    texture_paths = generate_textures(
        image_paths,
        creation_function,
        tmp_dir,
        sprite_suffix
    )
    sprite_paths = generate_blender_sprites(
        model_path = model_path,
        texture_paths = texture_paths,
        script_path = script_path,
        output_dir = tmp_dir,
    )
    processed_sprite_paths = process_sprites(
        sprite_paths,
        result_dir,
    )
    return processed_sprite_paths

def generate_textures(image_paths, create_texture_function, output_dir, output_suffix):
    logger.info("Creating textures")
    texture_paths = []
    for img_path in image_paths:
        output_path = os.path.join(output_dir, output_suffix + os.path.basename(img_path))
        create_texture_function(img_path, output_path)
        texture_paths.append(output_path)
        logger.debug("Created sprite '" + output_path + "'")
    logger.debug("Created " + str(len(texture_paths)) + " textures")
    return texture_paths

def generate_blender_sprites(model_path, texture_paths, script_path, output_dir):
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
            output_dir] + texture_paths
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

    

    sprite_paths = []
    for ct in texture_paths:
        name, ext = os.path.basename(ct).split(".")
        directory = os.path.dirname(ct)
        for i in range(4):
            sprite_path = os.path.join(directory, name + str(i) + "." + ext)
            if not os.path.exists(sprite_path):
                logger.warn("Could not find '" + os.path.basename(sprite_path) + "', which should have been generated")
            else:
                sprite_paths.append(sprite_path)
                logger.debug("Created sprite '" + sprite_path + "'")
    logger.debug("Created " + str(len(sprite_paths)) + " sprites")
    return sprite_paths

def process_sprites(sprite_paths, output_dir):
    logger.info("Processing sprites")
    processed_sprite_paths = []
    for sprite_path in sprite_paths:
        sprite_name = os.path.basename(sprite_path)
        output_path = os.path.join(output_dir, sprite_name)
        process_image(sprite_path, output_path)
        processed_sprite_paths.append(output_path)
        logger.debug("Processed sprite '" + sprite_name + "'")
    logger.debug("Processed " + str(len(processed_sprite_paths)) + " sprites")
    return processed_sprite_paths
