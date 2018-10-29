/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(uint32_t seed, SDL_Renderer* renderer):
    rng { seed },
    cameraOrigin(0.f),
    atlas { renderer, "atlas.png" } {

    FillAtlas(atlas);

    constexpr int SIZE = 32;
    for (int y = -SIZE; y < SIZE; y++) {
        for (int x = -SIZE; x < SIZE; x++) {
            blocks.emplace(Point3i{ x, y, 0}, Block(MaterialType::GRASS, BlockType::CUBE, Direction::NORTH));
            
            if (rng() % 3 == 0) {
                blocks.emplace(Point3i{ x, y, 1 }, Block(MaterialType::ROCK, BlockType::CUBE, Direction::NORTH));
            }
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

void World::Draw(const RectI& rect) {
    static const Point2i tolerance { ATLAS_SPRITE_WIDTH, ATLAS_SPRITE_HEIGHT };
    for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
        Point2i screenPos = WorldToScreenPos(iter->first, cameraOrigin);
        if (rect.InBoundaries(screenPos, tolerance)) {
            atlas.DrawSprite(iter->second, screenPos);
        }
    }
}

void World::DrawSpriteAtlas(const RectI& rect) {
    atlas.DrawRegisteredSprites(rect);
}

}   // namespace dwarfs
