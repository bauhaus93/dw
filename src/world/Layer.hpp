/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>
#include <array>
#include <memory>
#include <algorithm>

#include <SDL.h>

#include "utility/Point2.hpp"
#include "utility/Point3.hpp"
#include "utility/Rect.hpp"
#include "utility/Defs.hpp"
#include "graphics/Sprite.hpp"
#include "block/Block.hpp"
#include "block/Volume.hpp"
#include "block/Material.hpp"
#include "block/BlockType.hpp"
#include "block/ProtoBlockSet.hpp"
#include "Size.hpp"
#include "Transformation.hpp"
#include "Direction.hpp"
#include "HeightMap.hpp"


namespace dwarfs {

typedef std::array<std::array<std::unique_ptr<Volume>, LAYER_SIZE_X>, LAYER_SIZE_Y> VolumeGrid;

class Layer {
public:
                Layer(int32_t level_, const ProtoBlockSet& protoblocks_);
                Layer(int32_t level_, const ProtoBlockSet& protoblocks_, const HeightMap& heightMap);

    void        Draw(const Point3i& cameraOrigin, const RectI& rect);

private:
    void        CreateVolume(Point2i pos,
                          Material blockMaterial, BlockType blockType,
                          Material floorMaterial);
    void        CreateVolumeFloorOnly(Point2i pos, Material floorMaterial);

    int32_t                             level;
    const ProtoBlockSet&                protoblocks;
    VolumeGrid                          volume;

};




}   // namespace dwarfs
