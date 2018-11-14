/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <memory>
#include <set>

#include <SDL.h>

#include "logger/GlobalLogger.hpp"
#include "graphics/SpriteAtlas.hpp"
#include "graphics/Sprite.hpp"
#include "Block.hpp"
#include "DirectionalBlock.hpp"
#include "Material.hpp"
#include "BlockType.hpp"

namespace dwarfs {

struct SharedBlockCmp {
    bool operator() (const std::shared_ptr<Block>& lhs, const std::shared_ptr<Block>& rhs) const {
        return lhs->CalculateId() < rhs->CalculateId();
    }
};

typedef std::set<std::shared_ptr<Block>, SharedBlockCmp> BlockSet;

class ProtoBlockSet {
public:
                                    ProtoBlockSet() = default;
                                    ProtoBlockSet(ProtoBlockSet&& other) = default;
    ProtoBlockSet&                  operator=(ProtoBlockSet&& rhs) = default;
    void                            AddBlock(std::shared_ptr<Block> prototype);
    std::shared_ptr<const Block>    GetPrototype(Material material, BlockType type) const;
    std::shared_ptr<const DirectionalBlock> GetPrototype(Material material, BlockType type, Direction dir) const;
    std::size_t                     GetCount() const { return prototypes.size(); }

private:
    BlockSet                    prototypes;
};


}   // namespace dwarfs
