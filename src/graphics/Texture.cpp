/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Texture.hpp"

namespace dwarfs {

Texture::Texture(SDL_Renderer* renderer_, const std::string& imgPath):
    Texture(renderer_) {
    LoadImage(imgPath);
}

Texture::Texture(SDL_Renderer* renderer_):
    Texture(renderer_, nullptr, Point2i(0, 0), 0) {
}

Texture::Texture(SDL_Renderer* renderer_, SDL_Texture* texture_, const Point2i& size_, uint32_t format_):
    renderer { renderer_ },
    texture { texture_ },
    size { size_ },
    format { format_ } {
    assert(renderer != nullptr);
}

Texture::~Texture() {
    if (texture != nullptr) {
        DEBUG("Destroying texture");
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
        assert(texture == nullptr);
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
    size[0] = w;
    size[1] = h;

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

Texture Texture::RenderSubTexture(const RectI& rect) const {
    INFO("Creating a new subtexture");
    SDL_Texture* subTex = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, rect[2], rect[3]);
    if (subTex == nullptr) {
        throw SDLError("SDL_CreateTexture");
    }
    if (SDL_SetRenderTarget(renderer, subTex) < 0) {
        throw SDLError("SDL_SetRenderTarget");
    }
    if (SDL_RenderClear(renderer) < 0) {
        throw SDLError("SDL_RenderClear");
    }
    SDL_Rect src { rect[0], rect[1], rect[2], rect[3] };
    if (SDL_RenderCopy(renderer, texture, &src, nullptr) < 0) {
        throw SDLError("SDL_RenderCopy");
    }
    //SDL_RenderPresent(renderer);

    if (SDL_SetRenderTarget(renderer, nullptr) < 0) {
        throw SDLError("SDL_SetRenderTarget");
    }
    if (SDL_SetTextureBlendMode(subTex, SDL_BLENDMODE_BLEND) < 0) {
         throw SDLError("SDL_SetTextureBlendMode");
    }
    return Texture(renderer, subTex, Point2i(rect[2], rect[3]), format);
}

Texture Texture::CreateSubTexture(const RectI& rect) const {
    SDL_BlendMode prevBlendMode;
    SDL_BlendMode prevRenderBlendMode;

    if (SDL_GetTextureBlendMode(texture, &prevBlendMode) < 0) {
        throw SDLError("SDL_GetTextureBlendMode");
    }
    if (SDL_GetRenderDrawBlendMode(renderer, &prevRenderBlendMode) < 0) {
        throw SDLError("SDL_GetTextureBlendMode");
    }

    if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) < 0) {
         throw SDLError("SDL_SetTextureBlendMode");
    }
    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
         throw SDLError("SDL_SetRenderDrawBlendMode");
    }

    if (SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, SDL_ALPHA_TRANSPARENT) < 0) {
        throw SDLError("SDL_SetRenderDrawColor");
    }
    Texture subTex = RenderSubTexture(rect);

    if (SDL_SetTextureBlendMode(texture, prevBlendMode) < 0) {
        throw SDLError("SDL_SetTextureBlendMode");
    }
    if (SDL_SetRenderDrawBlendMode(renderer, prevRenderBlendMode) < 0) {
         throw SDLError("SDL_SetRenderDrawBlendMode");
    }
    return subTex;
}

Texture Texture::CreateSubTextureBlendWhite(const RectI& rect) const {
    static SDL_BlendMode blendMode = SDL_ComposeCustomBlendMode(
        SDL_BLENDFACTOR_ZERO,
        SDL_BLENDFACTOR_ONE,
        SDL_BLENDOPERATION_ADD,
        SDL_BLENDFACTOR_ONE,
        SDL_BLENDFACTOR_ZERO,
        SDL_BLENDOPERATION_ADD
    );
    SDL_BlendMode prevBlendMode;
    if (SDL_GetTextureBlendMode(texture, &prevBlendMode) < 0) {
        throw SDLError("SDL_GetTextureBlendMode");
    }
    if (SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_TRANSPARENT) < 0) {
        throw SDLError("SDL_SetRenderDrawColor");
    }
    if (SDL_SetTextureBlendMode(texture, blendMode) < 0) {
         throw SDLError("SDL_SetTextureBlendMode");
    }
    Texture subTex = RenderSubTexture(rect);
    if (SDL_SetTextureBlendMode(texture, prevBlendMode) < 0) {
        throw SDLError("SDL_SetTextureBlendMode");
    }
    return subTex;
}

void Texture::SetColorMod(uint8_t r, uint8_t g, uint8_t b) const {
    if (SDL_SetTextureColorMod(texture, r, g, b) < 0) {
        throw SDLError("SDL_SetTextureColorMod");
    }
}

void Texture::ClearColorMod() const {
    SetColorMod(0xFF, 0xFF, 0xFF);
}

void Texture::DrawRect(const RectI& srcRect, const Point2i& dest) const {
    assert(texture != nullptr);
    assert(renderer != nullptr);
    SDL_Rect src { srcRect[0], srcRect[1], srcRect[2], srcRect[3] };
    SDL_Rect target { dest[0], dest[1], srcRect[2], srcRect[3] };
    if (SDL_RenderCopy(renderer, texture, &src, &target) < 0) {
        throw SDLError("SDL_RenderCopy");
    }
}

void Texture::Draw(const Point2i& dest) const {
    assert(texture != nullptr);
    assert(renderer != nullptr);
    SDL_Rect target { dest[0], dest[1], size[0], size[1] };
    if (SDL_RenderCopy(renderer, texture, nullptr, &target) < 0) {
        throw SDLError("SDL_RenderCopy");
    }
}



}   // namespace dwarfs
