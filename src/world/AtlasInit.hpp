/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>
#include <array>

#include "logger/GlobalLogger.hpp"
#include "utility/Point2.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "MaterialType.hpp"
#include "BlockType.hpp"
#include "Direction.hpp"
#include "Size.hpp"
#include "Block.hpp"

namespace dwarfs {

void FillBlockAtlas(SpriteAtlas<Block>& atlas);


}   // namespace dwarfs

