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

class Texture {
public:
                    Texture(SDL_Renderer* renderer_, const std::string& imgPath);
                    Texture(SDL_Renderer* renderer_);
                    Texture(SDL_Renderer* renderer_, SDL_Texture* texture_, const Point2i& size_, uint32_t format_);

                    ~Texture();
                    Texture(Texture&& other);
                    Texture(const Texture& other) = delete;
    Texture&        operator=(Texture&& other);
    Texture&        operator=(const Texture& other) = delete;

    void            LoadImage(const std::string& imgPath);
    Texture         CreateSubTexture(const RectI& rect) const;
    Texture         CreateSubTextureBlendWhite(const RectI& rect) const;
    void            SetColorMod(uint8_t r, uint8_t g, uint8_t b) const;
    void            ClearColorMod() const;
    void            DrawRect(const RectI& src, const Point2i& dest) const;
    void            Draw(const Point2i& dest) const;
private:
    Texture         RenderSubTexture(const RectI& rect) const;
    SDL_Renderer*               renderer;
    SDL_Texture*                texture;
    Point2i                     size;
    uint32_t                    format;
};

}   // namespace dwarfs
