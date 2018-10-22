import os
import sys
import sys
import bpy

script_args = sys.argv[sys.argv.index("--") + 1:]

script_dir = script_args[0]
if not script_dir in sys.path:
    sys.path.append(script_dir)

from utility import setup, add_texture
from blender_object import BlenderObject

output_path = script_args[1]
textures = script_args[2:]

print(textures)

setup()
[add_texture(t) for t in textures]
    
cube = BlenderObject("Cube")
cube.render_with_all_textures(output_path)
