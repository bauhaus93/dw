/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(SDL_Renderer* renderer):
    viewCenter { 0, 0, 0 },
    atlas { renderer, "atlas.png" } {
    LoadSprites();

    for (int y = -32; y < 32; y++) {
        for (int x = -32; x < 32; x++) {
            if (x == 0 && y == 0)
                blocks.emplace(Point3i(x, y, 0), Block(MaterialType::MUD, BlockType::CUBE, Direction::NORTH));
            else
                blocks.emplace(Point3i(x, y, 0), Block(MaterialType::GRASS, BlockType::CUBE, Direction::NORTH));
        }
    }
}

void World::SetViewCenter(const Point3i& newCenter) {
    viewCenter = newCenter;
}

void World::Draw(const RectI& rect) {
    Point2i center { viewCenter[0], viewCenter[1] };
    for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
        Point2i screenPos = WorldToScreenPos(Point2i(iter->first[0], iter->first[1]), center);
        if (rect.InBoundaries(screenPos)) {
            atlas.DrawSprite(sprites.at(iter->second), screenPos);
        }
    }
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
        currPos[0] = rect[0];
        currPos[1] += atlas_format::SPRITE_HEIGHT;
    }
}

void World::LoadSprites() {
    INFO("Loading sprites");
    Point2i currPos(0);
    const Point2i SPRITE_SIZE { atlas_format::SPRITE_WIDTH, atlas_format::SPRITE_HEIGHT };
    int c = 0;
    for (int i = 0; i < atlas_format::MATERIAL_COUNT; i++) {
        for (int j = 0; j < atlas_format::TYPE_COUNT; j++) {
            for (int k = 0; k < atlas_format::DIRECTION_COUNT; k++) {
                RectI rect { currPos, SPRITE_SIZE };
                Block block { atlas_format::MATERIALS[i], atlas_format::TYPES[j], atlas_format::DIRECTIONS[k] };
                if (atlas_format::TYPES[j] == BlockType::CUBE) {
                    block.SetDirection(Direction::NORTH);
                }
                Sprite sprite = atlas.GetSprite(rect);
                sprites.insert(std::make_pair<Block, Sprite>(std::move(block), std::move(sprite)));
                c++;
                currPos[0] += SPRITE_SIZE[0];
                if (atlas_format::TYPES[j] == BlockType::CUBE) {
                    break;
                }
            }
        }
        currPos[0] = 0;
        currPos[1] += SPRITE_SIZE[1];
    }
    INFO("Loaded ", c, " sprites");

}

}   // namespace dwarfs
