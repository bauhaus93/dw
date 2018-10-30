/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>

#include "AtlasInit.hpp"

namespace dwarfs {

constexpr int32_t ATLAS_SPRITE_WIDTH = 64;
constexpr int32_t ATLAS_SPRITE_HEIGHT = 74;

constexpr int32_t TILE_WIDTH = ATLAS_SPRITE_WIDTH;
constexpr int32_t TILE_HEIGHT = TILE_WIDTH / 2;

constexpr int32_t LAYER_SIZE_X = 64;
constexpr int32_t LAYER_SIZE_Y = LAYER_SIZE_X;

}   // namespace dwarfs