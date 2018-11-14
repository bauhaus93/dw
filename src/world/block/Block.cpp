/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Block.hpp"

namespace dwarfs {

Block::Block(Sprite sprite_, Material material_, BlockType type_):
    sprite { sprite_ },
    material { material_ },
    type { type_ } {
}

void Block::Draw(const Point2i dest, SDL_Renderer* renderer) const {
    sprite.Draw(dest, renderer);
}

int Block::CalculateId() const {
    return ToUnderlying(GetMaterial()) + MATERIAL_COUNT * ToUnderlying(GetType());
}

}   // namespace dwarfs
