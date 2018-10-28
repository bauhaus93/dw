/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <map>
#include <array>
#include <utility>

#include "utility/Rect.hpp"
#include "utility/Point2.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "graphics/Sprite.hpp"
#include "MaterialType.hpp"
#include "BlockType.hpp"
#include "Block.hpp"
#include "AtlasFormat.hpp"
#include "Direction.hpp"

namespace dwarfs {


class World {
public:
                    World(SDL_Renderer* renderer);

    void            Draw(const RectI& rect);
    void            DrawLoadedSprites(const RectI& rect);

private:
    SpriteAtlas             atlas;
    std::map<Block, Sprite> sprites;

    void            LoadSprites();

};




}   // namespace dwarfs
