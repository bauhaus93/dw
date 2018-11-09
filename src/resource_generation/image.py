import cv2 as cv
import numpy as np

def translate_image(img, offX, offY):
    h, w = img.shape[:2]
    shift = np.float32([[1, 0, offX], [0, 1, offY]])
    img = cv.warpAffine(img, shift, (w, h))
    return img[:-2 * abs(offY), :-2* abs(offX)]

def resize_to_width(img, target_width):
    height, width = img.shape[:2]
    if height != width:
        target_height = round(target_width * height / width)
        return cv.resize(img, (target_width, target_height))
    else:
        return cv.resize(img, (target_width, target_width))

def change_brightness(img, factor):
    hsv = cv.cvtColor(img[:, :, :3], cv.COLOR_RGB2HSV)
    h, s, v = cv.split(hsv.astype(np.float))
    v = cv.multiply(v, factor)
    hsv_merged = cv.merge((h, s, v))
    rgb = cv.cvtColor(hsv_merged.astype(np.uint8), cv.COLOR_HSV2RGB)
    r, g, b = cv.split(rgb)
    return cv.merge((r, g, b, img[:, :, 3]))

def process_image(src, target_width, dest):
    #shift factor only changes, if we change the blender camera/object distance/angle
    SHIFT_FACTOR_X = 0.09765625
    SHIFT_FACTOR_Y = 0.03125

    img = cv.imread(src, cv.IMREAD_UNCHANGED)
    w, h, _ = img.shape
    shift_x = round(-w * SHIFT_FACTOR_X)
    shift_y = round(-h * SHIFT_FACTOR_Y)

    img = translate_image(img, shift_x, shift_y)
    img = resize_to_width(img, target_width)

    cv.imwrite(dest, img)