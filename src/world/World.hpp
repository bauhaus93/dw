/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <map>
#include <array>
#include <utility>
#include <cmath>
#include <random>
#include <vector>

#include "utility/Rect.hpp"
#include "utility/Point2.hpp"
#include "utility/Point3.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "atlas_init/BlockAtlas.hpp"
#include "MaterialType.hpp"
#include "BlockType.hpp"
#include "Layer.hpp"
#include "Block.hpp"
#include "Direction.hpp"
#include "Transformation.hpp"
#include "SimplexNoise.hpp"
#include "HeightMap.hpp"

namespace dwarfs {

class World {
public:
                    World(uint32_t seed, SDL_Renderer* renderer);

    void            CenterCamera(const Point2i& worldPos, Point2i& windowCenter);
    void            SetCamera(const Point3i& newOrigin);
    void            CameraUp();
    void            CameraDown();
    void            SetCameraByScreenPos(const Point2i& screenPos);
    void            Draw(const RectI& rect);
    void            DrawSpriteAtlas(const RectI& rect);

private:
    std::mt19937                rng;
    Point3i                     cameraOrigin;
    SimplexNoise                heightNoise;
    SpriteAtlas                 blockAtlas;
    std::map<Block, uint32_t>   blockSpriteIds;
    std::map<int32_t, Layer>    layer;

    void            LoadSprites();

};




}   // namespace dwarfs
