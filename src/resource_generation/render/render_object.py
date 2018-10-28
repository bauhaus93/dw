import os
import sys
import argparse
import bpy

script_dir = os.path.dirname(__file__)
if not script_dir in sys.path:
    sys.path.append(script_dir)

from utility import setup, add_texture, iter_camera_views, set_camera_position, set_camera_direction
from blender_object import BlenderObject

parser = argparse.ArgumentParser("Renders objects in blender")
parser.add_argument("--output-dir",
                    metavar = "DIRECTORY",
                    help = "Specify the output directory",
                    required = True)
parser.add_argument("--texture-paths",
                    metavar = "FILE",
                    nargs = "+",
                    help = "Specify the textures to use",
                    required = True)
parser.add_argument("--camera-angles",
                    metavar = "INTEGER",
                    nargs = "+",
                    help = "Specify the different camera angles to render",
                    type = int,
                    choices = [0, 1, 2, 3],
                    default = [0, 1, 2, 3],
                    required = False)
args = parser.parse_args(sys.argv[sys.argv.index("--") + 1:])

setup()
[add_texture(t) for t in args.texture_paths]
 
obj = BlenderObject("Object")
cam_views = [e for e in enumerate(iter_camera_views())]
cam_views = [cam_views[i] for i in args.camera_angles]
for (index, (cam_pos, cam_dir)) in cam_views:
    set_camera_position(cam_pos)
    set_camera_direction(cam_dir)
    obj.render_with_all_textures(args.output_dir, index)
