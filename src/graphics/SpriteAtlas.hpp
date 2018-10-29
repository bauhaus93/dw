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
#include "world/Block.hpp"
#include "SDLError.hpp"
#include "SDLImgError.hpp"

namespace dwarfs {

class SpriteAtlas {
public:
                    SpriteAtlas(SDL_Renderer* renderer_, const std::string& file);
                    ~SpriteAtlas();
                    SpriteAtlas(SpriteAtlas&& other);
    SpriteAtlas&    operator=(SpriteAtlas&& other);

    void            RegisterBlockSprite(const Block& blockPrototype, const RectI& spriteRect);
    void            DrawSprite(const Block& block, const Point2i& dest);
    void            DrawRegisteredSprites(const RectI& rect);
private:
    SDL_Renderer*           renderer;
    SDL_Texture*            texture;
    RectI                   size;
    uint32_t                format;
    std::map<Block, RectI>  blocks;


};


}   // namespace dwarfs
