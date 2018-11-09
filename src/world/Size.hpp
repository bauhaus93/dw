/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>

namespace dwarfs {

constexpr float SPRITE_RATIO = 1.171875;

constexpr int32_t ATLAS_SPRITE_WIDTH = 64;
constexpr int32_t ATLAS_SPRITE_HEIGHT = static_cast<int>(static_cast<float>(ATLAS_SPRITE_WIDTH) * SPRITE_RATIO);

constexpr int32_t TILE_WIDTH = ATLAS_SPRITE_WIDTH;
constexpr int32_t TILE_HEIGHT = TILE_WIDTH / 2;

constexpr int32_t LAYER_SIZE_X = 64;
constexpr int32_t LAYER_SIZE_Y = LAYER_SIZE_X;

}   // namespace dwarfs