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
                Layer(int32_t level_, const SpriteAtlas& blockAtlas, const std::map<Block, uint32_t>& blockSprites);
                Layer(int32_t level_, const SpriteAtlas& blockAtlas_, const std::map<Block, uint32_t>& blockSprites_, const HeightMap& heightMap);

    void        Draw(const Point3i& cameraOrigin, const RectI& rect);

private:

    int32_t                             level;
    const SpriteAtlas&                  blockAtlas;
    const std::map<Block, uint32_t>&    blockSprites;
    BlockGrid                           block;

};




}   // namespace dwarfs
