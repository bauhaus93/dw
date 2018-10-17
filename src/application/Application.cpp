/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Application.hpp"

namespace dwarfs {

Application::Application(uint32_t winSizeX, uint32_t winSizeY):
    stop { false },
    window { nullptr } {
    INFO("Creating application");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLError("SDL_Init");
    }

    window = SDL_CreateWindow(
        "Dwarfs",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        winSizeX,
        winSizeY,
        0
    );

    if (window == nullptr) {
        throw SDLError("SDL_CreateWindow");
    }

}

Application::~Application() {
    INFO("Destroying application");
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Application::Run() {

    while (!stop) {

        SDL_Delay(100);
    }
}

}   // namespace dwarfs
