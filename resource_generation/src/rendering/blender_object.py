import bpy
import os

class BlenderObject:
    
    def __init__(self, name):
        self.obj = bpy.data.objects[name]
        self.create_material()
        
    def create_material(self):
        material = bpy.data.materials.new(self.obj.name + "_Material")
        material_texture = material.texture_slots.add()
        material_texture.texture = None
        material_texture.texture_coords = 'UV'
        material_texture.mapping = 'FLAT'
        material_texture.scale[0] = 1
        material_texture.scale[1] = 1
        material_texture.scale[2] = 1
        
        if self.obj.data.materials:
            self.obj.data.materials[0] = material
        else:
            self.obj.data.materials.append(material)
        self.obj.active_material = material
    
    def set_material_texture(self, texture):
        self.obj.active_material.texture_slots[0].texture = texture
        
    def render_with_all_textures(self, output_path):
        for tex in bpy.data.textures:
            self.set_material_texture(tex)
            output_name = os.path.join(output_path, tex.name)
            bpy.data.scenes['Scene'].render.filepath = output_name
            bpy.ops.render.render(write_still=True)
        self.set_material_texture(None)
