import os

import cv2 as cv
import numpy as np

from texture_generation import common

def create_cube_texture(src, dest):
    BLACK = (0, 0, 0, 0xFF)

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    h, w, c = img.shape
    result = np.full((h * 4, w * 4, c), BLACK, np.uint8)
    
    cv.rectangle(img, (0, 0), (w, h), BLACK, common.LINE_WIDTH)

    offsets = [(0, 2 * h),
            (w, 2 * h),
            (2 * w, 2 * h),
            (3 * w, 2 * h),
            (2 * w, h),
            (2 * w, 3 * h)]

    for off in offsets:
        result[off[1]:off[1] + w, off[0]:off[0] + h] = img

    cv.imwrite(dest, result)