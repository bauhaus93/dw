/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(SDL_Renderer* renderer):
    atlas { renderer, "atlas.png" } {
    LoadSprites();
}

void World::Draw(const RectI& rect) {
    DrawLoadedSprites(rect);
}

void World::DrawLoadedSprites(const RectI& rect) {
    Point2i currPos = rect.GetOrigin();
    for (int i = 0; i < atlas_format::MATERIAL_COUNT; i++) {
        for (auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
            if (iter->first.GetMaterial() == atlas_format::MATERIALS[i]) {
                atlas.DrawSprite(iter->second, currPos);
                currPos[0] += atlas_format::SPRITE_WIDTH;
                if (!rect.InBoundaryX(currPos))  {
                    currPos[0] = 0;
                    currPos[1] += atlas_format::SPRITE_HEIGHT;
                }
            }
        }
        currPos[0] = 0;
        currPos[1] += atlas_format::SPRITE_HEIGHT;
    }
}

void World::LoadSprites() {
    INFO("Loading sprites");
    Point2i currPos(0);
    int c = 0;
    for (int i = 0; i < atlas_format::MATERIAL_COUNT; i++) {
        for (int j = 0; j < atlas_format::TYPE_COUNT; j++) {
            for (int k = 0; k < atlas_format::DIRECTION_COUNT; k++) {
                RectI rect { currPos[0], currPos[1], atlas_format::SPRITE_WIDTH, atlas_format::SPRITE_HEIGHT };
                Block block { atlas_format::MATERIALS[i], atlas_format::TYPES[j], atlas_format::DIRECTIONS[k] };
                Sprite sprite = atlas.GetSprite(rect);
                sprites.insert(std::make_pair<Block, Sprite>(std::move(block), std::move(sprite)));
                c++;
                currPos[0] += atlas_format::SPRITE_WIDTH;
                if (atlas_format::TYPES[j] == BlockType::CUBE) {
                    break;
                }
            }
        }
        currPos[0] = 0;
        currPos[1] += atlas_format::SPRITE_HEIGHT;
    }
    INFO("Loaded ", c, " sprites");

}

}   // namespace dwarfs
