#!/usr/bin/env python3
import os
import sys
import logging
import time
import argparse
import xml.etree.ElementTree as et


from atlas import create_atlas
import utility

start_time = time.perf_counter()

parser = argparse.ArgumentParser("Generates a sprite atlas using different materials and models.")
parser.add_argument("--xml-file",
                    metavar = "FILE",
                    help = "Specify the xml file used for generation",
                    required = True)
parser.add_argument("--result-dir",
                    metavar = "DIRECTORY",
                    help = "Specify the output directory",
                    required = True)
parser.add_argument("--render-script",
                    metavar = "FILE",
                    help = "Specify the python script invoked in blender",
                    required = True)
args = parser.parse_args()


utility.setup_logger()
logger = logging.getLogger()

logger.info("Started resource generation")

XML_PATH = os.path.abspath(args.xml_file)
RESOURCE_DIR = os.path.dirname(XML_PATH)
RENDER_SCRIPT_PATH = os.path.abspath(args.render_script)

logger.info("Resource dir: " + RESOURCE_DIR + "'")
logger.info("Render script: '" + RENDER_SCRIPT_PATH + "'")


logger.info("Parsing from file '" + XML_PATH + "'")
tree = et.parse(XML_PATH)
root = tree.getroot()
for child in root:
    create_atlas(child, RESOURCE_DIR, RENDER_SCRIPT_PATH)

logger.info("Resource generation finished in " + "{:.2f}".format(time.perf_counter() - start_time) + "s")