/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>

#include "graphics/Sprite.hpp"
#include "BlockType.hpp"
#include "MaterialType.hpp"
#include "Direction.hpp"

namespace dwarfs {

class Block {
public:

                    Block(MaterialType material_, BlockType kind_, Direction direction_);
    friend bool     operator<(const Block& rhs, const Block& lhs);
private:
    MaterialType    material;
    BlockType       kind;
    Direction       direction;
};


inline bool operator<(const Block& lhs, const Block& rhs) {
    if (lhs.kind < rhs.kind) {
        return true;
    } else if(lhs.kind == rhs.kind) {
        if (lhs.material < rhs.material)
            return true;
        else if (lhs.material == rhs.material) {
            return lhs.direction < rhs.direction;
        }
    }
    return false;
}

}   // namespace dwarfs
