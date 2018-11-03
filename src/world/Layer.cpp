/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Layer.hpp"

namespace dwarfs {

const Point2i DRAW_TOLERANCE { ATLAS_SPRITE_WIDTH, ATLAS_SPRITE_HEIGHT };

Layer::Layer(int32_t level_, const SpriteAtlas& blockAtlas_, const std::map<Block, uint32_t>& protoBlock_):
    level { level_ },
    blockAtlas { blockAtlas_ },
    protoBlock { protoBlock_ } {

    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            if (level < -5) {
                block[y][x] = std::make_unique<Block>(MaterialType::ROCK, BlockType::CUBE, Direction::NORTH);
                block[y][x]->SetSpriteId(protoBlock.at(*block[y][x]));
            } else {
                block[y][x] = std::make_unique<Block>(MaterialType::MUD, BlockType::CUBE, Direction::NORTH);
                block[y][x]->SetSpriteId(protoBlock.at(*block[y][x]));
            }
        }
    }
}

Layer::Layer(int32_t level_, const SpriteAtlas& blockAtlas_, const std::map<Block, uint32_t>& protoBlock_, const HeightMap& heightMap):
    level { level_ },
    blockAtlas { blockAtlas_ },
    protoBlock { protoBlock_ } {

    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            int32_t height = heightMap[y][x];
            if (level == height) {
                block[y][x] = std::make_unique<Block>(MaterialType::GRASS, BlockType::CUBE, Direction::NORTH);
                block[y][x]->SetSpriteId(protoBlock.at(*block[y][x]));
            } else if (level < height) {
                block[y][x] = std::make_unique<Block>(MaterialType::MUD, BlockType::CUBE, Direction::NORTH);
                block[y][x]->SetSpriteId(protoBlock.at(*block[y][x]));
            }
        }
    }
}

void Layer::Draw(const Point3i& cameraOrigin, const RectI& rect) {
    RectI worldBoundaries { 0, 0, LAYER_SIZE_X, LAYER_SIZE_Y };
    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            if (block[y][x] != nullptr) {
                Point2i screenPos = WorldToScreenPos(Point3i { x, y, level }, cameraOrigin);
                if (screenPos.InBoundaries(Point2i(-ATLAS_SPRITE_WIDTH, -ATLAS_SPRITE_HEIGHT), rect.GetSize())) {
                    blockAtlas.DrawSprite(block[y][x]->GetSpriteId(), rect.GetOrigin() + screenPos);
                }
            }
        }
    }
}


}   // namespace dwarfs
