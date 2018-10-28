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

                    Application(uint32_t winSizeX, uint32_t winSizeY);
                    ~Application();

    void            Run();
private:

    bool                    stop;
    SDL_Window*             window;
    SDL_Renderer*           renderer;
    std::unique_ptr<World>  world;


    void            HandleEvents();
};

}   // namespace dwarfs
