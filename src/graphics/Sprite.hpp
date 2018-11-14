/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <SDL.h>

#include "utility/Rect.hpp"
#include "SpriteAtlas.hpp"

namespace dwarfs {

class Sprite {
public:
                    Sprite(const RectI& rect, const SpriteAtlas& atlas);
                    Sprite(const Sprite& other) = default;
    Sprite&         operator=(const Sprite& rhs) = default;

    void            Draw(const Point2i& dest, SDL_Renderer* renderer) const;
private:
    RectI                   rect;
    const SpriteAtlas&      atlas;
};


}   // namespace dwarfs
