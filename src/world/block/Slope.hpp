/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include "graphics/Sprite.hpp"
#include "world/Direction.hpp"
#include "DirectionalBlock.hpp"
#include "Material.hpp"

namespace dwarfs {

class Slope: public DirectionalBlock {
public:
                Slope(Sprite sprite_, Material material_, Direction dir_);
private:

};

}   // namespace dwarfs
