import os

from generation import generate_textures, generate_sprites, process_sprites, clean_directory, add_file_suffix
from texture_generation.cube_generation import create_cube_texture

resource_path = os.path.abspath("resources")
source_path =   os.path.abspath("src")

model_path =    os.path.join(resource_path, "models")
image_path =    os.path.join(resource_path, "images")
tmp_path =      os.path.join(resource_path, "tmp")
result_path =   os.path.join(resource_path, "results")

image_names = ["grass.png"]

def generate_cube_sprites(image_names, model_path, image_path, tmp_path, result_path):
    texture_filepaths = generate_textures(
        image_names,
        image_path,
        tmp_path,
        create_cube_texture,
        "cube_"
    )
    sprite_filepaths = generate_sprites(
        model_filepath = os.path.join(model_path, "block.blend"),
        texture_filepaths = texture_filepaths,
        script_dir = os.path.join(source_path, "rendering"),
        script_name = "create_cube.py",
        output_path = tmp_path
    )
    processed_sprite_filepaths = process_sprites(
        sprite_filepaths,
        result_path
    )
    clean_directory(tmp_path)

clean_directory(tmp_path)
clean_directory(result_path)

generate_cube_sprites(image_names, model_path, image_path, tmp_path, result_path)