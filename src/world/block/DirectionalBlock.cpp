/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "DirectionalBlock.hpp"

namespace dwarfs {

DirectionalBlock::DirectionalBlock(Sprite sprite_, Material material_, BlockType type_, Direction direction_) :
    Block(sprite_, material_, type_),
    direction { direction_ } {
}

int DirectionalBlock::CalculateId() const {
    return CalculateId(GetMaterial(), GetType(), GetDirection());
}

int DirectionalBlock::CalculateId(Material mat, BlockType type, Direction dir) {
    return ToUnderlying(mat) + MATERIAL_COUNT * ToUnderlying(type) + MATERIAL_COUNT * BLOCKTYPE_COUNT * ToUnderlying(dir);
}

std::string DirectionalBlock::GetString() const {
    std::stringstream ss;
    ss << "Id = " << CalculateId()
    << ", Material = " << GetMaterial()
    << ", Type = " << GetType()
    << ", Direction = " << GetDirection();
    return ss.str();
}

}   // namespace dwarfs
