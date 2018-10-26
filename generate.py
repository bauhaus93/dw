#!/usr/bin/env python3
import os
import sys
import logging

def setup_logger():
    FORMAT = r"[%(asctime)-15s] %(levelname)s - %(message)s"
    DATE_FORMAT = r"%Y-%m-%d %H:%M:%S"
    logging.basicConfig(level = logging.INFO, format=FORMAT, datefmt = DATE_FORMAT)

RESGEN_DIR = os.path.join(os.path.dirname(__file__), "resource_generation")
if not RESGEN_DIR in sys.path:
    sys.path.append(RESGEN_DIR)

from resource_generation.generation import generate_sprites
from resource_generation.result_processing.atlas import create_atlas

RESOURCE_DIR = os.path.abspath("resources/")
IMAGE_DIR = os.path.join(RESOURCE_DIR, "images")
RESULT_DIR = os.path.join(RESOURCE_DIR, "results")
MODEL_DIR = os.path.join(RESOURCE_DIR, "models")
RENDER_SCRIPT_PATH = os.path.abspath("resource_generation/render/render_object.py")
ATLAS_PATH = os.path.join(RESULT_DIR, "atlas.png")

image_paths = []
for img_name in os.listdir(IMAGE_DIR):
    img_path = os.path.join(IMAGE_DIR, img_name)
    if os.path.isfile(img_path):
        image_paths.append(img_path)

setup_logger()
logger = logging.getLogger()

logger.info("Resource dir: '" + RESOURCE_DIR + "'")
logger.info("Result dir: '" + RESULT_DIR + "'")

sprite_map = {}

#create cube sprites
logger.info("Generating cube sprites")
sprites = generate_sprites(
    image_paths,
    os.path.join(MODEL_DIR, "cube.blend"),
    RENDER_SCRIPT_PATH,
    "cube",
    RESULT_DIR,
    "sprite_cube_"
)
for i in range(2):
    sprite_map[(0, i)] = sprites[i]
logger.info("Generated cube sprites")


create_atlas(sprite_map, ATLAS_PATH)