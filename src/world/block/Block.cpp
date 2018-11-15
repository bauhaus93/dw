/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Block.hpp"

namespace dwarfs {

Block::Block(Sprite sprite_, Material material_, BlockType type_):
    sprite { sprite_ },
    material { material_ },
    type { type_ } {
}

void Block::Draw(const Point2i dest) const {
    sprite.Draw(dest);
}

int Block::CalculateId() const {
    return CalculateId(GetMaterial(), GetType());
}

int Block::CalculateId(Material mat, BlockType type) {
    return ToUnderlying(mat) + MATERIAL_COUNT * ToUnderlying(type);
}

std::string Block::GetString() const {
    std::stringstream ss;
    ss << "Id = " << CalculateId()
    << ", Material = " << GetMaterial()
    << ", Type = " << GetType();
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Block& block) {
    os << block.GetString();
    return os;
}

}   // namespace dwarfs
