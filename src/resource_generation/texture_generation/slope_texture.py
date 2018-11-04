import os

import cv2 as cv
import numpy as np

from texture_generation import common
from image import change_brightness

def create_slope_texture(src, dest):
    BLACK = (0, 0, 0, 0xFF)

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    h, w, c = img.shape

    slope_len = round((2 * w**2)**0.5)
    size = max(h * 3, w * 2 + slope_len)
    result = np.full((size, size, c), BLACK, np.uint8)
    
    square_img = np.copy(img)
    square_img = change_brightness(square_img, common.SIDE_BRIGHTNESS_FACTOR)

    tria_img = np.copy(square_img)  #brightness already done

    slope_img = np.zeros((h, slope_len, c), np.uint8)
    slope_img[:h, :w] = img
    slope_img[:, w:] = img[:, :slope_img.shape[1] - w]

    result[size - 2 * h:size - h, 0:w] = square_img
    result[size - 2 * h:size - h, w:w + w] = square_img

    result[size - 3 * h: size - 2 * h, w:w + w] = tria_img
    result[size - h:, w:w + w] = np.flip(tria_img, 1)

    result[size - 2 * h: size - h, 2 * w:] = slope_img

    cv.imwrite(dest, result)
