/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

#include <pugixml.hpp>
#include <SDL.h>

#include "application/ApplicationError.hpp"
#include "logger/GlobalLogger.hpp"
#include "utility/Point2.hpp"
#include "utility/Defs.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "world/block/Material.hpp"
#include "world/block/BlockType.hpp"
#include "world/Direction.hpp"
#include "world/Size.hpp"
#include "world/block/Block.hpp"
#include "world/block/Cube.hpp"
#include "world/block/Slope.hpp"
#include "world/block/Floor.hpp"
#include "world/block/ProtoBlockSet.hpp"
#include "XMLAttributeError.hpp"
#include "XMLChildError.hpp"

namespace dwarfs {

ProtoBlockSet CreateBlockPrototypes(const std::string& xmlFile, SpriteAtlas& atlas, SDL_Renderer* renderer);


}   // namespace dwarfs

