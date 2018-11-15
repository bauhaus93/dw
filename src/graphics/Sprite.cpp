/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Sprite.hpp"

namespace dwarfs {


Sprite::Sprite(const Texture& texture_, const RectI& rect_):
    texture { texture_ },
    rect { rect_ } {
}

void Sprite::Draw(const Point2i& dest) const {
    texture.DrawRect(rect, dest);
}
    

}   // namespace dwarfs
