import os

import cv2 as cv
import numpy as np

def create_cube_texture(src, dest):
    BLACK = (0, 0, 0, 0xFF)
    LINE_WIDTH = 10

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    h, w, c = img.shape
    result = np.zeros((h * 4, w * 4, c), np.uint8)
    
    cv.rectangle(img, (0, 0), (w, h), BLACK, LINE_WIDTH)

    offsets = [(0, 2 * h),
            (w, 2 * h),
            (2 * w, 2 * h),
            (3 * w, 2 * h),
            (2 * w, h),
            (2 * w, 3 * h)]

    for off in offsets:
        result[off[1]:off[1] + w, off[0]:off[0] + h] = img

    cv.imwrite(dest, result)