/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Block.hpp"

namespace dwarfs {

Block::Block(MaterialType material_, BlockType type_, Direction direction_):
    material { material_ },
    type { type_ },
    direction { direction_ } {

}

void Block::SetType(BlockType newType) {
    type = newType;
}

void Block::SetDirection(Direction newDirection) {
    direction = newDirection;
}




}   // namespace dwarfs