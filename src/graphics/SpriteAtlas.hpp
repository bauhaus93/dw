/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>
#include <cassert>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "logger/GlobalLogger.hpp"
#include "utility/Rect.hpp"
#include "utility/Point2.hpp"
#include "SDLError.hpp"
#include "SDLImgError.hpp"

namespace dwarfs {

class SpriteAtlas {
public:
                    SpriteAtlas(SDL_Renderer* renderer_);
                    SpriteAtlas(SDL_Renderer* renderer_, const std::string& imgPath);

                    ~SpriteAtlas();
                    SpriteAtlas(SpriteAtlas&& other);
    SpriteAtlas&    operator=(SpriteAtlas&& other);

    void            LoadImage(const std::string& imgPath);
    uint32_t        RegisterSprite(const RectI& spriteRect);
    void            DrawSprite(uint32_t id, const Point2i& dest) const;
    void            DrawRegisteredSprites(const RectI& rect) const;
private:
    SDL_Renderer*               renderer;
    SDL_Texture*                texture;
    RectI                       size;
    uint32_t                    format;
    uint32_t                    nextId;
    std::map<uint32_t, RectI>   sprites;
};

}   // namespace dwarfs
