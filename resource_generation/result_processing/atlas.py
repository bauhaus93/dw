import logging

import cv2 as cv
import numpy as np

logger = logging.getLogger()

def create_atlas(sprite_paths_map, output_path):
    logger.info("Creating sprite atlas")
    max_coord = (max(k for (k, v) in sprite_paths_map.items()),
                 max(len(v) for (k, v) in sprite_paths_map.items()))

    sprite_map = {}
    sprite_shape = None
    for mat_index, sprite_list in sprite_paths_map.items():
        for (type_index, sprite_path) in enumerate(sprite_list):
            index_coord = (type_index, mat_index)
            logger.debug("Index: " + str(index_coord) + ", sprite: '" + sprite_path + "'")
            sprite_map[index_coord] = cv.imread(sprite_path, cv.IMREAD_UNCHANGED)
            if sprite_shape == None:
                sprite_shape = sprite_map[index_coord].shape
            elif sprite_map[index_coord].shape != sprite_shape:
                logger.error("Sprite '" + sprite_path + "' has different shape, expected: " + str(sprite_shape) + ", got: " + str(sprite_map[index_coord].shape))
                exit(1)
    atlas_shape = (sprite_shape[0] * (max_coord[0] + 1),
                  sprite_shape[1] * (max_coord[1] + 1),
                  sprite_shape[2])
 
    atlas = np.zeros(atlas_shape)
    logger.info("Creating atlas of shape " + str(atlas.shape))

    for index_coord, sprite in sprite_map.items():
        coord = (index_coord[0] * sprite_shape[1],
                 index_coord[1] * sprite_shape[0])
        atlas[coord[1]:coord[1] + sprite_shape[0], coord[0]:coord[0] + sprite_shape[1]] = sprite
    logger.info("Added " + str(len(sprite_map)) + " sprites to atlas")

    cv.imwrite(output_path, atlas)
    logger.info("Created sprite atlas '" + output_path + "'")