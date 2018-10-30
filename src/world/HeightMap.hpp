/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <array>
#include <cstdint>

#include "Size.hpp"
#include "SimplexNoise.hpp"

namespace dwarfs {

typedef std::array<std::array<int32_t, LAYER_SIZE_X>, LAYER_SIZE_Y> HeightMap;

HeightMap CreateHeightMap(const SimplexNoise& heightNoise);

}   // namespace dwarfs

    
