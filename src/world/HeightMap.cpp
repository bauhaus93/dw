/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "HeightMap.hpp"

namespace dwarfs {

HeightMap CreateHeightMap(const SimplexNoise& heightNoise) {
    HeightMap hm;

    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            hm[y][x] = static_cast<int32_t>(heightNoise.GetNoise(Point2i(x, y)));
        }
    }
    return hm;
}


}   // namespace dwarfs