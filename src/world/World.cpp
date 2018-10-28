/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(SDL_Renderer* renderer):
    atlas { renderer, "atlas.png" } {
    LoadSprites();
}

void World::Draw(int origX, int origY, int maxX, int maxY) {
    DrawLoadedSprites(origX, origY, maxX, maxY);
}

void World::DrawLoadedSprites(int origX, int origY, int maxX, int maxY) {
    int currX = origX;
    int currY = origY;
    for (int i = 0; i < atlas_format::MATERIAL_COUNT; i++) {
        for (auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
            if (iter->first.GetMaterial() == atlas_format::MATERIALS[i]) {
                atlas.DrawSprite(iter->second, currX, currY);
                currX += atlas_format::SPRITE_WIDTH;
                if (currX >= maxX)  {
                    currX = 0;
                    currY += atlas_format::SPRITE_HEIGHT;
                }
            }
        }
        currX = 0;
        currY += atlas_format::SPRITE_HEIGHT;
    }
}

void World::LoadSprites() {
    INFO("Loading sprites");
    int currX = 0;
    int currY = 0;
    int c = 0;
    for (int i = 0; i < atlas_format::MATERIAL_COUNT; i++) {
        for (int j = 0; j < atlas_format::TYPE_COUNT; j++) {
            for (int k = 0; k < atlas_format::DIRECTION_COUNT; k++) {
                Block block { atlas_format::MATERIALS[i], atlas_format::TYPES[j], atlas_format::DIRECTIONS[k] };
                Sprite sprite = atlas.GetSprite(currX, currY, atlas_format::SPRITE_WIDTH, atlas_format::SPRITE_HEIGHT);
                sprites.insert(std::make_pair<Block, Sprite>(std::move(block), std::move(sprite)));
                c++;
                currX += atlas_format::SPRITE_WIDTH;
                if (atlas_format::TYPES[j] == BlockType::CUBE) {
                    break;
                }
            }
        }
        currX = 0;
        currY += atlas_format::SPRITE_HEIGHT;
    }
    INFO("Loaded ", c, " sprites");

}

}   // namespace dwarfs
