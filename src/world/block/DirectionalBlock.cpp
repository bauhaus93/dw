/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "DirectionalBlock.hpp"

namespace dwarfs {

DirectionalBlock::DirectionalBlock(Sprite sprite_, Material material_, BlockType type_, Direction direction_) :
    Block(sprite_, material_, type_),
    direction { direction_ } {
}

int DirectionalBlock::CalculateId() const {
    return ToUnderlying(GetMaterial()) + MATERIAL_COUNT * ToUnderlying(GetType()) + MATERIAL_COUNT * BLOCKTYPE_COUNT * ToUnderlying(GetDirection());
}

}   // namespace dwarfs
