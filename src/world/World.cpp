/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "World.hpp"

namespace dwarfs {

World::World(SDL_Renderer* renderer):
    atlas { renderer, "atlas.png" },
    test { atlas.GetSprite(SDL_Rect{ 0, 0, 20, 20 }) } {

}


void World::Draw() {
    atlas.DrawSprite(test, 0, 0);
}

}   // namespace dwarfs
