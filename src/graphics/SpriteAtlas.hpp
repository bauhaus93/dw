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
                    SpriteAtlas();
                    SpriteAtlas(const std::string& imgPath, SDL_Renderer* renderer);

                    ~SpriteAtlas();
                    SpriteAtlas(SpriteAtlas&& other);
                    SpriteAtlas(const SpriteAtlas& other) = delete;
    SpriteAtlas&    operator=(SpriteAtlas&& other);
    SpriteAtlas&    operator=(const SpriteAtlas& other) = delete;

    void            LoadImage(const std::string& imgPath, SDL_Renderer* renderer);
    void            DrawRect(const RectI& src, const Point2i& dest, SDL_Renderer* renderer) const;
private:
    SDL_Texture*                texture;
    RectI                       size;
    uint32_t                    format;
};

}   // namespace dwarfs
