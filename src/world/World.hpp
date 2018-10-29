/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <map>
#include <array>
#include <utility>
#include <cmath>

#include "utility/Rect.hpp"
#include "utility/Point2.hpp"
#include "utility/Point3.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "graphics/Sprite.hpp"
#include "MaterialType.hpp"
#include "BlockType.hpp"
#include "Block.hpp"
#include "AtlasFormat.hpp"
#include "Direction.hpp"
#include "Transformation.hpp"

namespace dwarfs {


class World {
public:
                    World(SDL_Renderer* renderer);

    void            CenterCamera(const Point2i& worldPos, Point2i& windowCenter);
    void            SetCamera(const Point2i& newOrigin);
    void            SetCameraByScreenPos(const Point2i& screenPos);
    void            Draw(const RectI& rect);
    void            DrawLoadedSprites(const RectI& rect);

private:
    Point2i                     cameraOrigin;
    SpriteAtlas                 atlas;
    std::map<Block, Sprite>     sprites;
    std::map<Point3i, Block>    blocks;

    void            LoadSprites();

};




}   // namespace dwarfs
