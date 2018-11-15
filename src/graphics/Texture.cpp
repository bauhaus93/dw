/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Texture.hpp"

namespace dwarfs {

/*    SDL_BlendMode blendMode = SDL_ComposeCustomBlendMode(
        SDL_BLENDFACTOR_ZERO,
        SDL_BLENDFACTOR_DEST_COLOR,
        SDL_BLENDOPERATION_ADD,
        SDL_BLENDFACTOR_ONE,
        SDL_BLENDFACTOR_ZERO,
        SDL_BLENDOPERATION_ADD
    );
    SDL_SetTextureColorMod(texture, 10, 255, 255);*/

Texture::Texture(SDL_Renderer* renderer_):
    renderer { renderer_ },
    texture { nullptr },
    size { 0, 0, 0, 0 },
    format { 0 } {
}

Texture::Texture(SDL_Renderer* renderer_, const std::string& imgPath):
    Texture(renderer_) {
    LoadImage(imgPath);
}

Texture::~Texture() {
    if (texture != nullptr) {
        INFO("Destroying texture");
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

Texture::Texture(Texture&& other):
    renderer { other.renderer },
    texture { other.texture },
    size { other.size },
    format { other.format } {
    other.texture = nullptr;
}

Texture& Texture::operator=(Texture&& other) {
    if (this != &other ) {
        renderer = other.renderer;
        texture = other.texture;
        size = other.size;
        format = other.format;
        other.texture = nullptr;
    }
    return *this;
}

void Texture::LoadImage(const std::string& imgPath) {
    assert(renderer != nullptr);
    assert(texture == nullptr);
    INFO("Loading texture from img: '", imgPath, "'");

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

void Texture::DrawRect(const RectI& srcRect, const Point2i& dest) const {
    assert(texture != nullptr);
    assert(renderer != nullptr);
    SDL_Rect src { srcRect[0], srcRect[1], srcRect[2], srcRect[3] };
    SDL_Rect target { dest[0], dest[1], srcRect[2], srcRect[3] };
    SDL_RenderCopy(renderer, texture, &src, &target);
}

void Texture::Draw(const Point2i& dest) const {
    DrawRect(size, dest);
}



}   // namespace dwarfs
