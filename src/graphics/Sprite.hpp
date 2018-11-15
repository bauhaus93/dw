/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include "utility/Rect.hpp"
#include "Texture.hpp"

namespace dwarfs {

class Sprite {
public:
                    Sprite(const Texture& texture_, const RectI& rect);
                    Sprite(const Sprite& other) = default;
    Sprite&         operator=(const Sprite& rhs) = default;

    void            Draw(const Point2i& dest) const;
private:
    const Texture&          texture;
    RectI                   rect;
};


}   // namespace dwarfs
