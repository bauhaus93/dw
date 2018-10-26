import os

import cv2 as cv
import numpy as np

def create_slope_texture(src, dest):
    BLACK = (0, 0, 0, 0xFF)
    LINE_WIDTH = 10

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    h, w, c = img.shape

    slope_len = round((2 * w**2)**0.5)
    size = max(h * 3, w * 2 + slope_len)
    result = np.zeros((size, size, c), np.uint8)
    
    square_img = np.copy(img)
    cv.rectangle(square_img, (0, 0), (h, w), BLACK, 2 * LINE_WIDTH)

    tria_img = np.copy(square_img)
    cv.line(tria_img, (0, 0), (h, w), (0, 0, 0, 0xFF), LINE_WIDTH)

    slope_img = np.zeros((h, slope_len, c), np.uint8)
    slope_img[:h, :w] = img
    slope_img[:, w:] = img[:, :slope_img.shape[1] - w]
    cv.rectangle(slope_img, (0, 0), (slope_img.shape[1], slope_img.shape[0]), BLACK, 2 * LINE_WIDTH)

    result[size - 2 * h:size - h, 0:w] = square_img
    result[size - 2 * h:size - h, w:w + w] = square_img

    rot_mat = cv.getRotationMatrix2D((tria_img.shape[1] / 2, tria_img.shape[0] / 2), 90, 1)
    tria_rot_img = cv.warpAffine(tria_img, rot_mat, (w, h))
    result[size - 3 * h: size - 2 * h, w:w + w] = tria_img
    result[size - h:, w:w + w] = tria_rot_img

    result[size - 2 * h: size - h, 2 * w:] = slope_img

    cv.imwrite(dest, result)