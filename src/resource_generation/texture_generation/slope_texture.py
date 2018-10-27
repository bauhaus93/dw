import os

import cv2 as cv
import numpy as np

from texture_generation import common

def create_slope_texture(src, dest):
    BLACK = (0, 0, 0, 0xFF)

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    h, w, c = img.shape

    slope_len = round((2 * w**2)**0.5)
    size = max(h * 3, w * 2 + slope_len)
    result = np.full((size, size, c), BLACK, np.uint8)
    
    square_img = np.copy(img)
    cv.rectangle(square_img, (0, 0), (w, h), BLACK, common.LINE_WIDTH)

    tria_img = np.copy(square_img)
    cv.line(tria_img, (0, 0), (w, h), (0, 0, 0, 0xFF), common.LINE_WIDTH)

    slope_img = np.zeros((h, slope_len, c), np.uint8)
    slope_img[:h, :w] = img
    slope_img[:, w:] = img[:, :slope_img.shape[1] - w]
    cv.rectangle(slope_img, (0, 0), (slope_img.shape[1], slope_img.shape[0]), BLACK, common.LINE_WIDTH)

    result[size - 2 * h:size - h, 0:w] = square_img
    result[size - 2 * h:size - h, w:w + w] = square_img

    result[size - 3 * h: size - 2 * h, w:w + w] = tria_img
    result[size - h:, w:w + w] = np.flip(tria_img, 1)

    result[size - 2 * h: size - h, 2 * w:] = slope_img

    cv.imwrite(dest, result)
