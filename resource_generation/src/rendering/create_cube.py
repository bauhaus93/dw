import os
import sys
import sys
import bpy

script_dir = os.path.dirname(__file__)
if not script_dir in sys.path:
    sys.path.append(script_dir)

from utility import setup, add_texture
from blender_object import BlenderObject

script_args = sys.argv[sys.argv.index("--") + 1:]

output_path = script_args[0]
textures = script_args[1:]

print(textures)

setup()
[add_texture(t) for t in textures]
    
cube = BlenderObject("Cube")
cube.render_with_all_textures(output_path)
