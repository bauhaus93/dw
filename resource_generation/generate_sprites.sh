#!/bin/sh

source env/bin/activate
python src/generate.py --script src/rendering/create_cube.py --model resources/models/block.blend --result resources/results/ --image-directory resources/images/