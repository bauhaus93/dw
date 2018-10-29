/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "SpriteAtlas.hpp"

namespace dwarfs {

SpriteAtlas::SpriteAtlas(SDL_Renderer* renderer_, const std::string& file):
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
    renderer { other.renderer },
    texture { other.texture },
    size { other.size },
    format { other.format },
    blocks { std::move(other.blocks) } {
    other.texture = nullptr;
}

SpriteAtlas& SpriteAtlas::operator=(SpriteAtlas&& other) {
    if (this != &other ) {
        renderer = other.renderer;
        texture = other.texture;
        size = other.size;
        format = other.format;
        blocks = std::move(other.blocks);
        other.texture = nullptr;
    }
    return *this;
}

void SpriteAtlas::RegisterBlockSprite(const Block& blockPrototype, const RectI& spriteRect) {
    assert(blocks.find(blockPrototype) == blocks.end());
    blocks.emplace(blockPrototype, spriteRect);
}

void SpriteAtlas::DrawSprite(const Block& block, const Point2i& dest) {
    assert(blocks.find(block) != blocks.end());
    const RectI& srcRect = blocks.at(block);
    SDL_Rect src { srcRect[0], srcRect[1], srcRect[2], srcRect[3] };
    SDL_Rect target { dest[0], dest[1], srcRect[2], srcRect[3] };
    SDL_RenderCopy(renderer, texture, &src, &target);
}

void SpriteAtlas::DrawRegisteredSprites(const RectI& rect) {
    Point2i currPos = rect.GetOrigin();
    for (auto iter = blocks.begin(); iter != blocks.end(); ++iter) {
        DrawSprite(iter->first, currPos);
        currPos[0] += iter->second[2];
        if (currPos[0] >= rect[2]) {
            currPos[0] = rect[0];
            currPos[1] += iter->second[3];
        }
    }
}

}   // namespace dwarfs
