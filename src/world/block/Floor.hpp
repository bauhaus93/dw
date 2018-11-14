/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <SDL.h>

#include "graphics/Sprite.hpp"
#include "Block.hpp"
#include "Material.hpp"

namespace dwarfs {

class Floor: public Block {
public:
                Floor(Sprite sprite_, Material material_);
private:

};

}   // namespace dwarfs
