import os
import sys
import sys
import bpy

script_dir = os.path.dirname(__file__)
if not script_dir in sys.path:
    sys.path.append(script_dir)

from utility import setup, add_texture, iter_camera_views, set_camera_position, set_camera_direction
from blender_object import BlenderObject

script_args = sys.argv[sys.argv.index("--") + 1:]

output_path = script_args[0]
textures = script_args[1:]

setup()
[add_texture(t) for t in textures]
    
obj = BlenderObject("Object")
for (index, (cam_pos, cam_dir)) in enumerate(iter_camera_views()):
    set_camera_position(cam_pos)
    set_camera_direction(cam_dir)
    obj.render_with_all_textures(output_path, index)
