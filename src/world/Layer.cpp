/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Layer.hpp"

namespace dwarfs {

Layer::Layer(int32_t level_, const ProtoBlockSet& protoblocks_):
    level { level_ },
    protoblocks { protoblocks_ } {

    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            Point2i pos(x, y);
            if (level < -5) {
                CreateVolume(pos, Material::ROCK, BlockType::CUBE, Material::ROCK);   
            } else {
                CreateVolume(pos, Material::MUD, BlockType::CUBE, Material::MUD);
            }
        }
    }
}

Layer::Layer(int32_t level_, const ProtoBlockSet& protoblocks_, const HeightMap& heightMap):
    level { level_ },
    protoblocks { protoblocks_ } {

    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            int32_t height = heightMap[y][x];
            Point2i pos(x, y);
            if (level == height) {
                CreateVolumeFloorOnly(pos, Material::GRASS);
              } else if (level < height) {
                CreateVolume(pos, Material::MUD, BlockType::CUBE, Material::MUD);
            }
        }
    }
}


void Layer::CreateVolumeFloorOnly(Point2i pos, Material floorMaterial) {
    auto floor = protoblocks.GetPrototype(floorMaterial, BlockType::FLOOR);
    volume[pos[1]][pos[0]] = std::make_unique<Volume>(std::static_pointer_cast<const Floor>(floor));
}

void Layer::CreateVolume(Point2i pos,
                         Material blockMaterial, BlockType blockType, 
                         Material floorMaterial) {
    auto block = protoblocks.GetPrototype(blockMaterial, blockType);
    auto floor = protoblocks.GetPrototype(floorMaterial, BlockType::FLOOR);
    volume[pos[1]][pos[0]] = std::make_unique<Volume>(block, std::static_pointer_cast<const Floor>(floor));
}

void Layer::Draw(const Point3i& cameraOrigin, const RectI& rect) {
    RectI worldBoundaries { 0, 0, LAYER_SIZE_X, LAYER_SIZE_Y };
    for (int32_t y = 0; y < LAYER_SIZE_Y; y++) {
        for (int32_t x = 0; x < LAYER_SIZE_X; x++) {
            if (volume[y][x] != nullptr) {
                Point2i screenPos = WorldToScreenPos(Point3i { x, y, level }, cameraOrigin);
                if (screenPos.InBoundaries(Point2i(-TILE_WIDTH, -ATLAS_SPRITE_HEIGHT), rect.GetSize())) {
                    volume[y][x]->Draw(screenPos);
                }
            }
        }
    }
}


}   // namespace dwarfs
