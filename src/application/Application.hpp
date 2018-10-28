/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "logger/GlobalLogger.hpp"
#include "graphics/SDLError.hpp"
#include "world/World.hpp"

namespace dwarfs {

class Application {
  public:

                    Application(int winSizeX, int winSizeY);
                    ~Application();

    void            Run();
private:

    bool                    stop;
    SDL_Window*             window;
    int                     winX;
    int                     winY;
    SDL_Renderer*           renderer;

    std::unique_ptr<World>  world;

    void            Draw();
    void            HandleEvents();
};

}   // namespace dwarfs
