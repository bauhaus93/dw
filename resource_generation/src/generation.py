import os
import subprocess

from result_processing.process_image import process_image

def generate_textures(image_names, src_path, output_path, create_texture_function, output_suffix):
    print("+++ Generating textures +++")
    texture_filepaths = []
    for img_name in image_names:
        src_filepath = os.path.join(src_path, img_name)
        output_filepath = os.path.join(output_path, output_suffix + img_name)
        create_texture_function(src_filepath, output_filepath)
        texture_filepaths.append(output_filepath)

        print("Created texture:\t", "'" + os.path.basename(output_filepath) + "'")
    print("Created textures:\t", len(texture_filepaths))
    print("+++ Finished generating textures +++")
    return texture_filepaths

def generate_sprites(model_filepath, texture_filepaths, script_dir, script_name, output_path):
    print("+++ Generating sprites +++")
    print("Used model:\t\t", "'" + os.path.basename(model_filepath) + "'")
    print("Used script:\t\t", "'" + script_name + "'")
    [print("Used textures:\t\t", "'" + os.path.basename(t) + "'") for t in texture_filepaths]
    cmd = [ "blender",
            model_filepath,
            "--background",
            "--python",
            os.path.join(script_dir, "create_cube.py"),
            "--",
            script_dir,
            output_path] + texture_filepaths
    try:
        with open(os.devnull, "w") as f:
            subprocess.check_call(cmd, stdout = f, stderr = f)
    except subprocess.CalledProcessError:
        print("Error occured on sprite generation")
        exit(1)

    sprite_filepaths = []
    for ct in texture_filepaths:
        name = os.path.basename(ct)
        path = os.path.dirname(ct)
        sprite_filepath = os.path.join(path, "sprite_" + name)
        if not os.path.exists(sprite_filepath):
            print("Could not find ", "'" + os.path.basename(sprite_filepath) + "'", ", which should have been generated")
        else:
            sprite_filepaths.append(sprite_filepath)
    print("Generated sprites:\t", len(sprite_filepaths))
    print("+++ Finished generating sprites +++")
    return sprite_filepaths

def process_sprites(sprite_filepaths, output_path):
    print("+++ Processing sprites +++")
    processed_sprite_filepaths = []
    for sprite_filepath in sprite_filepaths:
        sprite_name = os.path.basename(sprite_filepath)
        output_filepath = os.path.join(output_path, sprite_name)
        process_image(sprite_filepath, output_filepath)
        print("Processed sprites:\t", "'" + sprite_name + "'")
        processed_sprite_filepaths.append(output_filepath)
    print("Processed sprites:\t", len(processed_sprite_filepaths))
    print("+++ Finished processing sprites +++")
    return processed_sprite_filepaths

def clean_directory(path):
    for filename in os.listdir(path):
        file_path = os.path.join(path, filename)
        if os.path.isfile(file_path):
            os.unlink(file_path)

def add_file_suffix(file_paths, suffix):
    for file_path in file_paths:
        new_filepath = os.path.join(os.path.dirname(file_path),
                                    suffix + os.path.basename(file_path))
        os.rename(file_path, new_filepath)



