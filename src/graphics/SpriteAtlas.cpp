/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "SpriteAtlas.hpp"

namespace dwarfs {

static uint32_t nextAtlasId = 0;

SpriteAtlas::SpriteAtlas(SDL_Renderer* renderer_, const std::string& file):
    id { nextAtlasId++ },
    renderer { renderer_ },
    texture { nullptr },
    size { 0, 0, 0, 0 },
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

SpriteAtlas::~SpriteAtlas() {
    if (texture != nullptr) {
        INFO("Destroying sprite atlas texture");
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    renderer = nullptr;
}

    uint32_t        id;
    SDL_Renderer*   renderer;
    SDL_Texture*    texture;
    Point2i         size;
    uint32_t        format;

SpriteAtlas::SpriteAtlas(SpriteAtlas&& other):
    id { other.id },
    renderer { other.renderer },
    texture { other.texture },
    size { other.size },
    format { other.format } {
    other.texture = nullptr;
}

SpriteAtlas& SpriteAtlas::operator=(SpriteAtlas&& other) {
    if (this != &other ) {
        id = other.id;
        renderer = other.renderer;
        texture = other.texture;
        size = other.size;
        format = other.format;
        other.texture = nullptr;
    }
    return *this;
}

Sprite SpriteAtlas::GetSprite(const RectI& r) const {
    assert(size.InBoundaries(r));
    return Sprite(id, r);
}

void SpriteAtlas::DrawSprite(const Sprite& sprite, const Point2i& dest) {
    assert(renderer != nullptr);
    assert(texture != nullptr);
    const RectI& sRect = sprite.GetRect();
    SDL_Rect src { sRect[0], sRect[1], sRect[2], sRect[3] };
    SDL_Rect target { dest[0], dest[1], sRect[2], sRect[3] };
    SDL_RenderCopy(renderer, texture, &src, &target);
}

}   // namespace dwarfs
