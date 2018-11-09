/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "SpriteAtlas.hpp"

namespace dwarfs {

SpriteAtlas::SpriteAtlas(SDL_Renderer* renderer_):
    renderer { renderer_ },
    texture { nullptr },
    size { 0, 0, 0, 0 },
    format { 0 },
    nextId { 0 } {
    assert(renderer != nullptr);
}

SpriteAtlas::SpriteAtlas(SDL_Renderer* renderer_, const std::string& imgPath):
    renderer { renderer_ },
    texture { nullptr },
    size { 0, 0, 0, 0 },
    format { 0 },
    nextId { 0 } {
    assert(renderer != nullptr);
    LoadImage(imgPath);
}

SpriteAtlas::~SpriteAtlas() {
    if (texture != nullptr) {
        INFO("Destroying sprite atlas texture");
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    renderer = nullptr;
}

SpriteAtlas::SpriteAtlas(SpriteAtlas&& other):
    renderer { other.renderer },
    texture { other.texture },
    size { other.size },
    format { other.format },
    nextId { other.nextId },
    sprites { std::move(other.sprites) } {
    other.texture = nullptr;
}

SpriteAtlas& SpriteAtlas::operator=(SpriteAtlas&& other) {
    if (this != &other ) {
        assert(texture == nullptr);
        renderer = other.renderer;
        texture = other.texture;
        size = other.size;
        format = other.format;
        nextId = other.nextId;
        sprites = std::move(other.sprites);
        other.texture = nullptr;
    }
    return *this;
}

void SpriteAtlas::LoadImage(const std::string& imgPath) {
    assert(renderer != nullptr);
    INFO("Loading sprite atlas img: '", imgPath, "'");

    SDL_Surface* surf = IMG_Load(imgPath.c_str());
    if (surf == nullptr) {
        throw SDLImgError("IMG_Load");
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

uint32_t SpriteAtlas::RegisterSprite(const RectI& spriteRect) {
    sprites.emplace(nextId, spriteRect);
    return nextId++;
}

void SpriteAtlas::DrawSprite(uint32_t id, const Point2i& dest) const {
    assert(texture != nullptr);
    assert(sprites.find(id) != sprites.end());
    const RectI& srcRect = sprites.at(id);
    SDL_Rect src { srcRect[0], srcRect[1], srcRect[2], srcRect[3] };
    SDL_Rect target { dest[0], dest[1], srcRect[2], srcRect[3] };
    SDL_RenderCopy(renderer, texture, &src, &target);
}

void SpriteAtlas::DrawRegisteredSprites(const RectI& rect) const {
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