/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Floor.hpp"

namespace dwarfs {

Floor::Floor(Sprite sprite_, Material material_):
    Block(sprite_, material_, BlockType::FLOOR) {
}

}   // namespace dwarfs
