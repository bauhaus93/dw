import os
import math

import bpy

def setup(force_clear = False):
    camera_setup()
    scene_setup()
    clear_textures(force_clear)
    clear_images(force_clear)

def camera_setup():
    try:
        camera = bpy.data.objects['Camera']
    except KeyError:
        camera = bpy.data.cameras.new("Camera")
        camera_obj = bpy.data.objects.new("Camera", camera)
        bpy.context.scene.objects.link(camera_obj)
        
        camera = bpy.data.objects['Camera']
        bpy.context.scene.camera = camera
        
    camera.rotation_euler[0] = math.atan(2**0.5)
    camera.rotation_euler[1] = 0
    camera.rotation_euler[2] = math.radians(45)
    camera.location[0] = 6.5
    camera.location[1] = -6.5
    camera.location[2] = 6
    
    camera.data.ortho_scale = 3.4
    camera.data.type = 'ORTHO'
    camera.data.shift_y = 0.12

def scene_setup():
    scene = bpy.context.scene

    scene.render.engine = 'BLENDER_RENDER'
    scene.render.resolution_x = 256
    scene.render.resolution_y = 256
    scene.render.resolution_percentage = 100
    scene.render.use_antialiasing = False
    scene.render.alpha_mode = 'TRANSPARENT'
    scene.render.image_settings.color_mode = 'RGBA'

    scene.world.light_settings.use_environment_light = True
    scene.world.light_settings.environment_energy = 1.0

def set_camera_position(new_pos):
    camera = bpy.data.objects['Camera']
    camera.location = new_pos

def set_camera_direction(new_dir):
    camera = bpy.data.objects['Camera']
    camera.rotation_euler = new_dir

def iter_camera_views():
    direction = (math.atan(2**0.5), 0, math.radians(45))
    pos = (6.5, -6.5, 6)
    pos_change = [(1, 1, 1),
                  (1, -1, 1),
                  (-1, -1, 1),
                  (-1, 1, 1)]
    for i in range(4):
        curr_pos = tuple(l * r for l, r in zip(pos, pos_change[i]))
        curr_dir = tuple(l + r for l, r in zip(direction, (0, 0, math.radians(90 * i))))
        yield (curr_pos, curr_dir)

def add_texture(image_path):
    img_name = os.path.basename(image_path).split(".")[0].lower()
    
    tex = bpy.data.textures.new(img_name, type='IMAGE')
    tex.use_mipmap = False
    tex.extension = 'CLIP'
    tex.image = bpy.data.images.load(image_path)

def clear_textures(force = False):
    for tex in bpy.data.textures:
        if force or (not tex.users):
            bpy.data.textures.remove(tex)

def clear_images(force = False):
    for img in bpy.data.images:
        if force or (not img.users):
            bpy.data.images.remove(img)