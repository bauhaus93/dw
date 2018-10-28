/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include "graphics/SpriteAtlas.hpp"

namespace dwarfs {

class World {
public:
                    World(SDL_Renderer* renderer);

    void            Draw();

private:
    SpriteAtlas     atlas;
    Sprite          test;


};




}   // namespace dwarfs
