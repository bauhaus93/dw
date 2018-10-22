#!/bin/sh

source env/bin/activate
python src/generate.py --script src/rendering/create_cube.py --model resources/models/block.blend --type cube --result resources/results/ --image-directory resources/images/ --suffix sprite_cube_