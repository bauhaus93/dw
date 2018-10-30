/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>
#include <cassert>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "logger/GlobalLogger.hpp"
#include "utility/Rect.hpp"
#include "utility/Point2.hpp"
#include "SDLError.hpp"
#include "SDLImgError.hpp"

namespace dwarfs {

template<class T>
class SpriteAtlas {
public:
                    SpriteAtlas(SDL_Renderer* renderer_, const std::string& file);
                    ~SpriteAtlas();
                    SpriteAtlas(SpriteAtlas&& other);
    SpriteAtlas&    operator=(SpriteAtlas&& other);

    void            RegisterSprite(const T& prototype, const RectI& spriteRect);
    void            DrawSprite(const T& protoype, const Point2i& dest);
    void            DrawRegisteredSprites(const RectI& rect);
private:
    SDL_Renderer*           renderer;
    SDL_Texture*            texture;
    RectI                   size;
    uint32_t                format;
    std::map<T, RectI>      sprites;
};

template<class T>
SpriteAtlas<T>::SpriteAtlas(SDL_Renderer* renderer_, const std::string& file):
    renderer { renderer_ },
    texture { nullptr },
    size { 0, 0, 0, 0 },
    format { 0 } {
    INFO("Creating sprite atlas: '", file, "'");
    assert(renderer != nullptr);

    SDL_Surface* surf = IMG_Load(file.c_str());
    if (surf == nullptr) {
        throw SDLImgError("SDL_Surface");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr) {
        SDL_FreeSurface(surf);
        throw SDLError("SDL_CreateTextureFromSurface");
    }
    SDL_FreeSurface(surf);

    int w = 0, h = 0;
    if (SDL_QueryTexture(texture, &format, nullptr, &w, &h) < 0) {
        throw SDLError("SDL_QueryTexture");
    }
    size[2] = w;
    size[3] = h;

    INFO("Size: ", size);

    switch(format) {
        case SDL_PIXELFORMAT_RGBA8888:  INFO("Format: RGBA8888");  break;
        case SDL_PIXELFORMAT_ARGB8888:  INFO("Format: ARGB8888");  break;
        case SDL_PIXELFORMAT_RGB888:    INFO("Format: RGB888");    break;
        case SDL_PIXELFORMAT_BGR888:    INFO("Format: GBR888");    break;
        case SDL_PIXELFORMAT_RGBA32:    INFO("Format: RGBA32");    break;
        case SDL_PIXELFORMAT_ARGB32:    INFO("Format: ARGB32");    break;
        default:                        INFO("Format: Unhandled"); break;
    }
}

template<class T>
SpriteAtlas<T>::~SpriteAtlas() {
    if (texture != nullptr) {
        INFO("Destroying sprite atlas texture");
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    renderer = nullptr;
}

template<class T>
SpriteAtlas<T>::SpriteAtlas(SpriteAtlas&& other):
    renderer { other.renderer },
    texture { other.texture },
    size { other.size },
    format { other.format },
    sprites { std::move(other.sprites) } {
    other.texture = nullptr;
}

template<class T>
SpriteAtlas<T>& SpriteAtlas<T>::operator=(SpriteAtlas&& other) {
    if (this != &other ) {
        renderer = other.renderer;
        texture = other.texture;
        size = other.size;
        format = other.format;
        sprites = std::move(other.sprites);
        other.texture = nullptr;
    }
    return *this;
}

template<class T>
void SpriteAtlas<T>::RegisterSprite(const T& prototype, const RectI& spriteRect) {
    assert(sprites.find(prototype) == sprites.end());
    sprites.emplace(prototype, spriteRect);
}

template<class T>
void SpriteAtlas<T>::DrawSprite(const T& prototype, const Point2i& dest) {
    assert(sprites.find(prototype) != sprites.end());
    const RectI& srcRect = sprites.at(prototype);
    SDL_Rect src { srcRect[0], srcRect[1], srcRect[2], srcRect[3] };
    SDL_Rect target { dest[0], dest[1], srcRect[2], srcRect[3] };
    SDL_RenderCopy(renderer, texture, &src, &target);
}

template<class T>
void SpriteAtlas<T>::DrawRegisteredSprites(const RectI& rect) {
    Point2i currPos = rect.GetOrigin();
    for (auto iter = sprites.begin(); iter != sprites.end(); ++iter) {
        DrawSprite(iter->first, currPos);
        currPos[0] += iter->second[2];
        if (currPos[0] >= rect[2]) {
            currPos[0] = rect[0];
            currPos[1] += iter->second[3];
        }
    }
}


}   // namespace dwarfs
