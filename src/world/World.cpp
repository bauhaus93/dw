/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(SDL_Renderer* renderer):
    cameraOrigin(0.f),
    atlas { renderer, "atlas.png" } {

    FillAtlas(atlas);

    constexpr int SIZE = 32;
    for (int y = -SIZE; y < SIZE; y++) {
        for (int x = -SIZE; x < SIZE; x++) {
            if (x == 0 && y == 0)
                blocks.emplace(Point3i(x, y, 0), Block(MaterialType::MUD, BlockType::CUBE, Direction::NORTH));
            else
                blocks.emplace(Point3i(x, y, 0), Block(MaterialType::GRASS, BlockType::CUBE, Direction::NORTH));
        }
    }
}

void World::CenterCamera(const Point2i& worldPos, Point2i& windowCenter) {
    SetCamera(ScreenToWorldPos(windowCenter * -1, worldPos));
}

void World::SetCamera(const Point2i& newOrigin) {
    cameraOrigin = newOrigin;
}

void World::SetCameraByScreenPos(const Point2i& centeredScreenPos) {
    SetCamera(ScreenToWorldPos(centeredScreenPos, cameraOrigin));
}

void World::Draw(const RectI& rect) {
    static const Point2i tolerance { TILE_WIDTH, TILE_HEIGHT };
    for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
        Point2i screenPos = WorldToScreenPos(Point2i(iter->first[0], iter->first[1]), cameraOrigin);
        if (rect.InBoundaries(screenPos, tolerance)) {
            atlas.DrawSprite(iter->second, screenPos);
        }
    }
}

void World::DrawSpriteAtlas(const RectI& rect) {
    atlas.DrawRegisteredSprites(rect);
}

}   // namespace dwarfs
