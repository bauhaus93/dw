/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "SpriteAtlas.hpp"

namespace dwarfs {

static uint32_t nextAtlasId = 0;

SpriteAtlas::SpriteAtlas(SDL_Renderer* renderer_, const std::string& file):
    id { nextAtlasId++ },
    renderer { renderer_ },
    texture { nullptr },
    w { -1 },
    h { -1 },
    format { 0 } {
    INFO("Loading sprite atlas: '", file, "'");
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

    if (SDL_QueryTexture(texture, &format, nullptr, &w, &h) < 0) {
        throw SDLError("SDL_QueryTexture");
    }
    INFO("Size: ", w, "x", h);
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

SpriteAtlas::~SpriteAtlas() {
    if (texture != nullptr) {
        INFO("Destroying sprite atlas");
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    renderer = nullptr;
}

SpriteAtlas::SpriteAtlas(SpriteAtlas&& other):
    id { other.id },
    texture { other.texture } {
    other.texture = nullptr;
}

SpriteAtlas& SpriteAtlas::operator=(SpriteAtlas&& other) {
    id = other.id;
    texture = other.texture;
    other.texture = nullptr;
    return *this;
}

Sprite SpriteAtlas::GetSprite(const SDL_Rect& rect) const {
    assert(rect.x < w || rect.y < h);
    assert(rect.x + rect.w < w && rect.y + rect.h < h);
    return Sprite(id, rect);
}

void SpriteAtlas::DrawSprite(const Sprite& sprite, int32_t destX, int32_t destY) {
    assert(renderer != nullptr);
    assert(texture != nullptr);
    const SDL_Rect* src = sprite.GetRect();
    SDL_Rect dest { destX, destY, src->w, src->h };
    SDL_RenderCopy(renderer, texture, src, &dest);
}

}   // namespace dwarfs
