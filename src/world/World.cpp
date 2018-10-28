/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(SDL_Renderer* renderer):
    atlas { renderer, "atlas.png" } {
    LoadSprites();
}


void World::Draw(int origX, int origY, int sizeX, int sizeY) {
    int currX = origX;
    int currY = origY;
    for (auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
        atlas.DrawSprite(iter->second, currX, currY);
        currX += SPRITE_WIDTH;
        if (currX >= sizeX)  {
            currX = 0;
            currY += SPRITE_HEIGHT;
        }
    }
}

void World::LoadSprites() {
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
        Direction::NORTH,
        Direction::EAST,
        Direction::SOUTH,
        Direction::WEST
    };
    INFO("Loading sprites");
    int currX = 0;
    int currY = 0;
    int c = 0;
    for (int i = 0; i < MATERIAL_COUNT; i++) {
        for (int j = 0; j < TYPE_COUNT; j++) {
            for (int k = 0; k < DIRECTION_COUNT; k++) {
                Block block { MATERIALS[i], TYPES[j], DIRECTIONS[k] };
                Sprite sprite = atlas.GetSprite(currX, currY, SPRITE_WIDTH, SPRITE_HEIGHT);
                sprites.insert(std::make_pair<Block, Sprite>(std::move(block), std::move(sprite)));
                c++;
                currX += SPRITE_WIDTH;
                if (TYPES[j] == BlockType::CUBE) {
                    break;
                }
            }
        }
        currX = 0;
        currY += SPRITE_HEIGHT;
    }
    INFO("Loaded ", c, " sprites");

}

}   // namespace dwarfs
