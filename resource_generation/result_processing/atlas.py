import operator
import logging

import cv2 as cv
import numpy as np

logger = logging.getLogger()

def create_atlas(sprite_path_map, output_path):
    logger.info("Creating sprite atlas")
    max_coord = (max(sprite_path_map, key = operator.itemgetter(0))[0],
                 max(sprite_path_map, key = operator.itemgetter(1))[1])

    sprite_map = {}
    sprite_size = None
    for index_coord, sprite_path in sprite_path_map.items():
        sprite_map[index_coord] = cv.imread(sprite_path, cv.IMREAD_UNCHANGED)
        if sprite_size == None:
            sprite_size = sprite_map[index_coord].shape
        elif sprite_map[index_coord].shape != sprite_size:
            logger.error("Sprite '" + sprite_path + "' has different shape, expected: " + str(sprite_size) + ", got: " + str(sprite_map[index_coord].shape))
            exit(1)
    atlas_size = (sprite_size[0] * (max_coord[1] + 1),
                  sprite_size[1] * (max_coord[0] + 1))
 
    atlas = np.zeros((atlas_size[0], atlas_size[1], sprite_size[2]))
    logger.info("Creating atlas of shape " + str(atlas.shape))

    for index_coord, sprite in sprite_map.items():
        coord = (index_coord[0] * sprite_size[1],
                 index_coord[1] * sprite_size[0])

        atlas[coord[1]:coord[1] + sprite_size[0], coord[0]:coord[0] + sprite_size[1]] = sprite
    logger.info("Added " + str(len(sprite_map)) + " sprites to atlas")

    cv.imwrite(output_path, atlas)
    logger.info("Created atlas sprite '" + output_path + "'")