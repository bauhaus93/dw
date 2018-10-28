/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <map>
#include <array>
#include <utility>

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

    void            Draw(int origX, int orgiY, int maxX, int maxY);
    void            DrawLoadedSprites(int origX, int origY, int maxX, int maxY);

private:
    SpriteAtlas             atlas;
    std::map<Block, Sprite> sprites;

    void            LoadSprites();

};




}   // namespace dwarfs
