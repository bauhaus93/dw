/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Layer.hpp"

namespace dwarfs {

const Point2i DRAW_TOLERANCE { ATLAS_SPRITE_WIDTH, ATLAS_SPRITE_HEIGHT };

Layer::Layer(int32_t level_, const SimplexNoise& heightNoise):
    level { level_ } {

    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            int32_t height = static_cast<int32_t>(heightNoise.GetNoise(Point2i(x, y)));
            if (level < height) {
                if (level < -5) {
                    block[y][x] = std::make_unique<Block>(MaterialType::ROCK, BlockType::CUBE, Direction::NORTH);
                } else if (level < -2) {
                    block[y][x] = std::make_unique<Block>(MaterialType::MUD, BlockType::CUBE, Direction::NORTH);
                } else {
                    block[y][x] = std::make_unique<Block>(MaterialType::GRASS, BlockType::CUBE, Direction::NORTH);
                }
            }
        }
    }

}

void Layer::Draw(SpriteAtlas& atlas, const Point3i& cameraOrigin, const RectI& rect) {
    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            if (block[y][x] != nullptr) {
                Point2i screenPos = WorldToScreenPos(Point3i { x, y, level }, cameraOrigin);
                if (rect.InBoundaries(screenPos, DRAW_TOLERANCE)) {
                    atlas.DrawSprite(*block[y][x], screenPos);
                }
            }
        }
    }
}


}   // namespace dwarfs
