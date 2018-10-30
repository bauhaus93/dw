/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "AtlasInit.hpp"

namespace dwarfs {

constexpr int MATERIAL_COUNT = 3;
constexpr int TYPE_COUNT = 3;
constexpr int DIRECTION_COUNT = 4;

constexpr std::array<MaterialType, MATERIAL_COUNT> MATERIALS = {
    MaterialType::GRASS,
    MaterialType::ROCK,
    MaterialType::MUD
};

constexpr std::array<BlockType, TYPE_COUNT> TYPES = {
    BlockType::CUBE,
    BlockType::FLOOR,
    BlockType::SLOPE
};

constexpr std::array<Direction, DIRECTION_COUNT> DIRECTIONS = {
    Direction::WEST,
    Direction::NORTH,
    Direction::EAST,
    Direction::SOUTH
};

void FillAtlas(SpriteAtlas& atlas) {
    INFO("Filling sprite atlas");
    Point2i currPos(0);
    const Point2i SPRITE_SIZE { ATLAS_SPRITE_WIDTH, ATLAS_SPRITE_HEIGHT };
    int c = 0;
    for (int i = 0; i < MATERIAL_COUNT; i++) {
        for (int j = 0; j < TYPE_COUNT; j++) {
            for (int k = 0; k < DIRECTION_COUNT; k++) {
                RectI rect { currPos, SPRITE_SIZE };
                Block block { MATERIALS[i], TYPES[j], DIRECTIONS[k] };
                if (TYPES[j] == BlockType::CUBE ||
                    TYPES[j] == BlockType::FLOOR) {
                    block.SetDirection(Direction::NORTH);
                }
                atlas.RegisterBlockSprite(block, rect);
                c++;
                currPos[0] += SPRITE_SIZE[0];
                if (TYPES[j] == BlockType::CUBE ||
                    TYPES[j] == BlockType::FLOOR) {
                    break;
                }
            }
        }
        currPos[0] = 0;
        currPos[1] += SPRITE_SIZE[1];
    }
    INFO("Registered ", c, " elements in atlas");
}

}   // namespace dwarfs

