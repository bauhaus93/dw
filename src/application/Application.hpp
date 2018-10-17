/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "logger/GlobalLogger.hpp"
#include "SDLError.hpp"

namespace dwarfs {

class Application {
  public:

                    Application(uint32_t winSizeX, uint32_t winSizeY);
                    ~Application();

    void            Run();
private:

    bool                stop;
    SDL_Window*         window;
};

}   // namespace dwarfs
