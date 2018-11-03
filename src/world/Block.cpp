/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Block.hpp"

namespace dwarfs {

Block::Block(MaterialType material_, BlockType type_, Direction direction_):
    Block(material_, type_, direction_, 0) {
}

Block::Block(MaterialType material_, BlockType type_, Direction direction_, uint32_t spriteId_):
    material { material_ },
    type { type_ },
    direction { direction_ },
    spriteId { spriteId_ } {

}

void Block::SetType(BlockType newType) {
    type = newType;
}

void Block::SetDirection(Direction newDirection) {
    direction = newDirection;
}

void Block::SetSpriteId(uint32_t newId) {
    spriteId = newId;
}




}   // namespace dwarfs