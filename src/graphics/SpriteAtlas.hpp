/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>
#include <cassert>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "logger/GlobalLogger.hpp"
#include "utility/Rect.hpp"
#include "utility/Point2.hpp"
#include "SDLError.hpp"
#include "SDLImgError.hpp"
#include "Sprite.hpp"


namespace dwarfs {

class SpriteAtlas {
public:
                    SpriteAtlas(SDL_Renderer* renderer_, const std::string& file);
                    ~SpriteAtlas();
                    SpriteAtlas(SpriteAtlas&& other);
    SpriteAtlas&    operator=(SpriteAtlas&& other);

    uint32_t        GetId() const { return id; }
    Sprite          GetSprite(const RectI& rect) const;
    void            DrawSprite(const Sprite& sprite, const Point2i& dest);
private:
    uint32_t        id;
    SDL_Renderer*   renderer;
    SDL_Texture*    texture;
    RectI           size;
    uint32_t        format;


};


}   // namespace dwarfs
