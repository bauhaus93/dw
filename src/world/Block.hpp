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

                    Block(MaterialType material_, BlockType type_, Direction direction_);

    MaterialType    GetMaterial() const { return material; }
    BlockType       GetType() const { return type; }
    Direction       GetDirection() const { return direction; }
    friend bool     operator<(const Block& rhs, const Block& lhs);
private:
    MaterialType    material;
    BlockType       type;
    Direction       direction;
};


inline bool operator<(const Block& lhs, const Block& rhs) {
    if (lhs.material < rhs.material) {
        return true;
    } else if(lhs.material == rhs.material) {
        if (lhs.type < rhs.type)
            return true;
        else if (lhs.type == rhs.type) {
            return lhs.direction < rhs.direction;
        }
    }
    return false;
}

}   // namespace dwarfs
