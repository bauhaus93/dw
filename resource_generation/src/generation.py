import os
import subprocess
import tempfile

from result_processing.process_image import process_image
from texture_generation.cube_texture import create_cube_texture

def generate_sprites(image_paths, model_path, script_path, result_dir, sprite_suffix, print_blender_output = False):
    tmp_dir = tempfile.gettempdir()

    texture_paths = generate_textures(
        image_paths,
        create_cube_texture,
        tmp_dir,
        sprite_suffix
    )
    sprite_paths = generate_blender_sprites(
        model_path = model_path,
        texture_paths = texture_paths,
        script_path = script_path,
        output_dir = tmp_dir,
        print_blender_output = print_blender_output
    )
    processed_sprite_paths = process_sprites(
        sprite_paths,
        result_dir
    )
    return processed_sprite_paths

def generate_textures(image_paths, create_texture_function, output_dir, output_suffix):
    print("+++ Generating textures +++")
    texture_paths = []
    for img_path in image_paths:
        output_path = os.path.join(output_dir, output_suffix + os.path.basename(img_path))
        create_texture_function(img_path, output_path)
        texture_paths.append(output_path)
        print("Created texture:\t", "'" + os.path.basename(output_path) + "'")
    print("Created textures:\t", len(texture_paths))
    print("+++ Finished generating textures +++")
    return texture_paths

def generate_blender_sprites(model_path, texture_paths, script_path, output_dir, print_blender_output = False):
    print("+++ Generating sprites +++")
    print("Used model:\t\t", "'" + os.path.basename(model_path) + "'")
    print("Used script:\t\t", "'" + os.path.basename(script_path) + "'")
    [print("Used texture:\t\t", "'" + os.path.basename(t) + "'") for t in texture_paths]
    cmd = [ "blender",
            model_path,
            "--background",
            "--python",
            script_path,
            "--",
            output_dir] + texture_paths
    try:
        if print_blender_output:
            subprocess.check_call(cmd)
        else:
            with open(os.devnull, "w") as f:
                subprocess.check_call(cmd, stdout = f, stderr = f)
    except subprocess.CalledProcessError:
        print("Error occured on sprite generation")
        exit(1)

    sprite_paths = []
    for ct in texture_paths:
        name = os.path.basename(ct)
        directory = os.path.dirname(ct)
        sprite_path = os.path.join(directory, name)
        if not os.path.exists(sprite_path):
            print("Could not find ", "'" + os.path.basename(sprite_path) + "'", ", which should have been generated")
        else:
            sprite_paths.append(sprite_path)
    print("Generated sprites:\t", len(sprite_paths))
    print("+++ Finished generating sprites +++")
    return sprite_paths

def process_sprites(sprite_paths, output_dir):
    print("+++ Processing sprites +++")
    processed_sprite_paths = []
    for sprite_path in sprite_paths:
        sprite_name = os.path.basename(sprite_path)
        output_path = os.path.join(output_dir, sprite_name)
        process_image(sprite_path, output_path)
        print("Processed sprites:\t", "'" + sprite_name + "'")
        processed_sprite_paths.append(output_path)
    print("Processed sprites:\t", len(processed_sprite_paths))
    print("+++ Finished processing sprites +++")
    return processed_sprite_paths

def add_file_suffix(file_paths, suffix):
    for file_path in file_paths:
        new_filepath = os.path.join(os.path.dirname(file_path),
                                    suffix + os.path.basename(file_path))
        os.rename(file_path, new_filepath)



