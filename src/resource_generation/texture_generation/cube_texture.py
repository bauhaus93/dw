import os

import cv2 as cv
import numpy as np

from texture_generation import common
from process_image import change_brightness

def create_cube_texture(src, dest):
    BLACK = (0, 0, 0, 0xFF)

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    h, w, c = img.shape
    result = np.full((h * 4, w * 4, c), BLACK, np.uint8)

    img_dark = change_brightness(img, common.SIDE_BRIGHTNESS_FACTOR)

    #imgBordered = np.copy(img)
    #cv.rectangle(imgBordered, (0, 0), (w, h), BLACK, common.LINE_WIDTH)

    offsets = [(0, 2 * h),
            (w, 2 * h),
            (2 * w, 2 * h),
            (3 * w, 2 * h),
            (2 * w, h),
            (2 * w, 3 * h)]

    for i, off in enumerate(offsets):
        if i != 0:
            result[off[1]:off[1] + w, off[0]:off[0] + h] = img_dark
        else:
            result[off[1]:off[1] + w, off[0]:off[0] + h] = img

    cv.imwrite(dest, result)