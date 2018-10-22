import os
import argparse

from generation import generate_sprites

parser = argparse.ArgumentParser(description = "Generate sprites base on different textures and models")

parser.add_argument(
    "--script",
    nargs = 1,
    metavar = "FILE",
    required = True,
    help = "Specify the python script to invoke in blender during sprite generation"
)

parser.add_argument(
    "--model",
    nargs = 1,
    metavar = "FILE",
    required = True,
    help = "Specify the .blend file, which should be used for sprite generation"
)

parser.add_argument(
    "--result",
    nargs = 1,
    metavar = "DIR",
    required = True,
    help = "Specify the directory, where all results should be put"
)

parser.add_argument(
    "--suffix",
    nargs = 1,
    metavar = "SUFFIX",
    help = "Specify suffix added to each sprite"
)

group = parser.add_mutually_exclusive_group(required = True)
group.add_argument(
    "--image-directory",
    nargs = 1,
    metavar = "DIR",
    help = "Specify directory which should be scanned for images to use as textures"
)
group.add_argument(
    "--image-files",
    nargs = "+",
    metavar = "FILE",
    help = "Specify image files which should be used as textures"
)

args = parser.parse_args()

image_paths = []
if args.image_directory:
    abs_dir = os.path.abspath(args.image_directory[0])
    for filename in os.listdir(abs_dir):
        full_name = os.path.join(abs_dir, filename)
        if os.path.isfile(full_name):
            image_paths.append(full_name)
else:
    image_paths = [os.path.abspath(img) for img in args.image_files]

if args.suffix:
    suffix = args.suffix[0]
else:
    suffix = ""

model_path = os.path.abspath(args.model[0])
script_path = os.path.abspath(args.script[0])
result_dir = os.path.abspath(args.result[0])

generate_sprites(image_paths,model_path, script_path, result_dir, sprite_suffix = suffix)