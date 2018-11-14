/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Slope.hpp"

namespace dwarfs {

Slope::Slope(Sprite sprite_, Material material_, Direction direction_) :
    DirectionalBlock(sprite_, material_, BlockType::SLOPE, direction_) {
}

}   // namespace dwarfs
