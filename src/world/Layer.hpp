/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>
#include <array>
#include <memory>

#include "utility/Point2.hpp"
#include "utility/Point3.hpp"
#include "utility/Rect.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "Block.hpp"
#include "Size.hpp"
#include "Transformation.hpp"
#include "MaterialType.hpp"
#include "BlockType.hpp"
#include "Direction.hpp"
#include "HeightMap.hpp"


namespace dwarfs {

typedef std::array<std::array<std::unique_ptr<Block>, LAYER_SIZE_X>, LAYER_SIZE_Y> BlockGrid;

class Layer {
public:
    explicit    Layer(int32_t level_);
                Layer(int32_t level_, const HeightMap& heightMap);

    void        Draw(SpriteAtlas<Block>& blockAtlas, const Point3i& cameraOrigin, const RectI& rect);

private:

    int32_t     level;
    BlockGrid   block;

};




}   // namespace dwarfs
