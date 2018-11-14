/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Cube.hpp"

namespace dwarfs {

Cube::Cube(Sprite sprite_, Material material_):
    Block(sprite_, material_, BlockType::CUBE) {
}

}   // namespace dwarfs
