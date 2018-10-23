#!/usr/bin/env python3
import os
import sys
import logging

def setup_logger():
    FORMAT = r"[%(asctime)-15s] %(levelname)s - %(message)s"
    DATE_FORMAT = r"%Y-%m-%d %H:%M:%S"
    logging.basicConfig(level = logging.INFO, format=FORMAT, datefmt = DATE_FORMAT)

resgen_dir = os.path.join(os.path.dirname(__file__), "resource_generation")
if not resgen_dir in sys.path:
    sys.path.append(resgen_dir)

from resource_generation.generation import generate_sprites

RESOURCE_DIR = os.path.abspath("resources/")
IMAGE_DIR = os.path.join(RESOURCE_DIR, "images")
RESULT_DIR = os.path.join(RESOURCE_DIR, "results")
RENDER_SCRIPT_PATH = os.path.abspath("resource_generation/render/render_object.py")

image_paths = []
for img_name in os.listdir(IMAGE_DIR):
    img_path = os.path.join(IMAGE_DIR, img_name)
    if os.path.isfile(img_path):
        image_paths.append(img_path)

setup_logger()
logger = logging.getLogger()

logger.info("Resource dir: '" + RESOURCE_DIR + "'")
logger.info("Result dir: '" + RESULT_DIR + "'")

#create cube sprites
logger.info("Generating cube sprites")
generate_sprites(image_paths,
                 os.path.join(RESOURCE_DIR, "models", "cube.blend"),
                 RENDER_SCRIPT_PATH,
                 "cube",
                 RESULT_DIR,
                 "sprite_cube_")
logger.info("Generated cube sprites")