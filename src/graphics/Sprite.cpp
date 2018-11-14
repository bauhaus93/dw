/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Sprite.hpp"

namespace dwarfs {


Sprite::Sprite(const RectI& rect_, const SpriteAtlas& atlas_):
    rect { rect_ },
    atlas { atlas_ } {
}

void Sprite::Draw(const Point2i& dest, SDL_Renderer* renderer) const {
    atlas.DrawRect(rect, dest, renderer);
}
    

}   // namespace dwarfs
