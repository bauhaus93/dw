/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

#include <pugixml.hpp>

#include "application/ApplicationError.hpp"
#include "logger/GlobalLogger.hpp"
#include "utility/Point2.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "world/MaterialType.hpp"
#include "world/BlockType.hpp"
#include "world/Direction.hpp"
#include "world/Size.hpp"
#include "world/Block.hpp"
#include "XMLAttributeError.hpp"
#include "XMLChildError.hpp"

namespace dwarfs {

std::map<Block, uint32_t> FillBlockAtlas(const std::string& xmlFile, SpriteAtlas& atlas);


}   // namespace dwarfs

