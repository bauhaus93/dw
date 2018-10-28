/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>
#include <cassert>

#include <SDL2/SDL.h>

#include "logger/GlobalLogger.hpp"

namespace dwarfs {

class Sprite {
public:
                    Sprite(uint32_t atlasId_, const SDL_Rect& rect_);

                    Sprite(Sprite&& other) = default;
    Sprite&         operator=(Sprite&& other) = default;

    uint32_t        GetAtlasId() const { return atlasId; }
    const SDL_Rect* GetRect() const { return &rect; }       
private:

    uint32_t            atlasId;
    SDL_Rect            rect;
};


}   // namespace dwarfs
