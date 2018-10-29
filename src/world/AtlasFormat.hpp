/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>
#include <array>

#include "MaterialType.hpp"
#include "BlockType.hpp"
#include "Direction.hpp"

namespace dwarfs::atlas_format {

constexpr int32_t   SPRITE_WIDTH = 64;
constexpr int32_t   SPRITE_HEIGHT = 74;

constexpr int MATERIAL_COUNT = 3;
constexpr int TYPE_COUNT = 2;
constexpr int DIRECTION_COUNT = 4;

constexpr std::array<MaterialType, MATERIAL_COUNT> MATERIALS = {
    MaterialType::GRASS,
    MaterialType::MUD,
    MaterialType::ROCK
};

constexpr std::array<BlockType, TYPE_COUNT> TYPES = {
    BlockType::CUBE,
    BlockType::SLOPE
};

constexpr std::array<Direction, DIRECTION_COUNT> DIRECTIONS = {
    Direction::WEST,
    Direction::NORTH,
    Direction::EAST,
    Direction::SOUTH
};

}   // namespace dwarfs::atlas_format