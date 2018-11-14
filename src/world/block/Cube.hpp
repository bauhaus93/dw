/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include "utility/Defs.hpp"
#include "graphics/Sprite.hpp"
#include "Block.hpp"
#include "Material.hpp"

namespace dwarfs {

class Cube: public Block {
public:
                Cube(Sprite sprite_, Material material_);
private:

};

}   // namespace dwarfs
