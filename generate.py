#!/usr/bin/env python3
import os
import sys
import logging
import time

def setup_logger():
    FORMAT = r"[%(asctime)-15s] %(levelname)s - %(message)s"
    DATE_FORMAT = r"%Y-%m-%d %H:%M:%S"
    logging.basicConfig(level = logging.INFO, format = FORMAT, datefmt = DATE_FORMAT)

RESGEN_DIR = os.path.join(os.path.dirname(__file__), "resource_generation")
if not RESGEN_DIR in sys.path:
    sys.path.append(RESGEN_DIR)

from resource_generation.generation import generate_sprites
from resource_generation.result_processing.atlas import create_atlas

start_time = time.perf_counter()

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

if not os.path.isfile(RENDER_SCRIPT_PATH):
    logger.error("Could not find render script: '" + RENDER_SCRIPT_PATH + "'")
    exit(1)

block_types = ["cube", "slope"]
sprite_map = {}

for block_type in block_types:
    logger.info("Generating '" + block_type + "' sprites")
    model_name = os.path.join(MODEL_DIR, block_type + ".blend")
    if not os.path.isfile(model_name):
        logger.error("Model not existing: '" + model_name + "'")
        exit(1)
    sprites = generate_sprites(
        image_paths,
        os.path.join(MODEL_DIR, block_type + ".blend"),
        RENDER_SCRIPT_PATH,
        block_type,
        RESULT_DIR,
        "sprite_" + block_type + "_"
    )
    for i in range(0, len(sprites), 4):
        mat_index = int(i / 4)
        if block_type == "cube":
            items = 1
        else:
            items = 4
        if not mat_index in sprite_map:
            sprite_map[mat_index] = sprites[i:i + items]
        else:
            sprite_map[mat_index] += sprites[i:i + items]
    logger.info("Generated '" + block_type + "' sprites")

create_atlas(sprite_map, ATLAS_PATH)

logger.info("Finished in " + "{:.2f}".format(time.perf_counter() - start_time) + "s")