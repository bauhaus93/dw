/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Selection.hpp"

namespace dwarfs {

Selection::Selection(Sprite sprite_, Material material_):
    Block(sprite_, material_, BlockType::SELECTION) {
}

}   // namespace dwarfs
