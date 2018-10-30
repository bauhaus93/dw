#!/usr/bin/env python3
import os
import sys
import logging
import time
import argparse

from atlas import create_atlas
import utility

parser = argparse.ArgumentParser("Generates sprites, using different materials and models.")
parser.add_argument("--resource-dir",
                    metavar = "DIRECTORY",
                    help = "Specify the root dir of the resources",
                    required = True)
parser.add_argument("--result-dir",
                    metavar = "DIRECTORY",
                    help = "Specify the root dir of the results",
                    required = True)
args = parser.parse_args()

start_time = time.perf_counter()
utility.setup_logger()
logger = logging.getLogger()

logger.info("Started resource generation")

RESOURCE_DIR = os.path.abspath(args.resource_dir)
RESULT_DIR = os.path.abspath(args.result_dir)
MATERIAL_DIR = os.path.join(RESOURCE_DIR, "materials")
MODEL_DIR = os.path.join(RESOURCE_DIR, "models")
ATLAS_PATH = os.path.join(RESULT_DIR, "atlas.png")
RENDER_SCRIPT_PATH = os.path.abspath(os.path.join(os.path.dirname(sys.argv[0]), "render/render_object.py"))

BLOCK_TYPES = ["cube", "floor", "slope"]
MATERIAL_PATHS = utility.get_files_from_dir(MATERIAL_DIR, "png")

logger.info("Resource dir: " + RESOURCE_DIR)
logger.info("Result dir: " + RESULT_DIR)
logger.info("Block types: " + str(len(BLOCK_TYPES)))
logger.info("Materials: " + str(len(MATERIAL_PATHS)))

create_atlas(BLOCK_TYPES, MATERIAL_PATHS, MODEL_DIR, RENDER_SCRIPT_PATH, ATLAS_PATH)

logger.info("Resource generation finished in " + "{:.2f}".format(time.perf_counter() - start_time) + "s")