/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Sprite.hpp"

namespace dwarfs {

Sprite::Sprite(uint32_t atlasId_, const RectI& rect_):
    atlasId { atlasId_ },
    rect { rect_ } {
}

}   // namespace dwarfs