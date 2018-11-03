/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(uint32_t seed, SDL_Renderer* renderer):
    rng { seed },
    cameraOrigin(0.f),
    heightNoise { static_cast<uint32_t>(rng()) },
    blockAtlas { renderer, "atlas.png" },
    protoBlock { FillBlockAtlas(blockAtlas) } {

    heightNoise.SetMin(0);
    heightNoise.SetMax(4);
    heightNoise.SetRoughness(5.0);
    heightNoise.SetScale(0.001);

    FillBlockAtlas(blockAtlas);

    HeightMap hm = CreateHeightMap(heightNoise);

    for (int32_t level = 4; level > -10; level--) {
        if (level >= 0){
            layer.emplace(std::piecewise_construct,
                          std::forward_as_tuple(level),
                          std::forward_as_tuple(level, blockAtlas, protoBlock, hm));
        } else {
            layer.emplace(std::piecewise_construct,
                          std::forward_as_tuple(level),
                          std::forward_as_tuple(level, blockAtlas, protoBlock));
        }
    }
}

void World::CenterCamera(const Point2i& worldPos, Point2i& windowCenter) {
 //   SetCamera(ScreenToWorldPos(windowCenter * -1, worldPos));
}

void World::SetCamera(const Point3i& newOrigin) {
    cameraOrigin = newOrigin;
}

void World::SetCameraByScreenPos(const Point2i& centeredScreenPos) {
    Point2i p = ScreenToWorldPos(centeredScreenPos, Point2i { cameraOrigin[0], cameraOrigin[1] });
    SetCamera(Point3i { p[0], p[1], cameraOrigin[2] });
}

void World::CameraUp() {
    cameraOrigin[2]++;
    INFO("Curr layer: ", cameraOrigin[2]);
}
void World::CameraDown() {
    cameraOrigin[2]--;
    INFO("Curr layer: ", cameraOrigin[2]);
}

void World::Draw(const RectI& rect) {
    if (cameraOrigin[2] >= 0) {
        for (int32_t h = cameraOrigin[2] - 4; h < cameraOrigin[2] + 4; h++) {
            auto find = layer.find(h);
            if (find != layer.end()) {
                find->second.Draw(cameraOrigin, rect);
            } else {
                break;
            }
        }
    } else {
        auto find = layer.find(cameraOrigin[2]);
        if (find != layer.end()) {
            find->second.Draw(cameraOrigin, rect);
        }
    }
}

void World::DrawSpriteAtlas(const RectI& rect) {
    blockAtlas.DrawRegisteredSprites(rect);
}

}   // namespace dwarfs
