/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Application.hpp"

namespace dwarfs {

Application::Application(uint32_t winSizeX, uint32_t winSizeY):
    stop { false },
    window { nullptr },
    renderer { nullptr },
    world { nullptr } {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLError("SDL_Init");
    }
    INFO("Initalized SDL");

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
    INFO("Created window");

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr) {
        throw SDLError("SDL_CreateRenderer");
    }
    INFO("Created renderer");

    world = std::make_unique<World>(renderer);
}

Application::~Application() {
    if (world != nullptr) {
        INFO("Destroying world");
        world = nullptr;
    }
    if (renderer != nullptr) {
        INFO("Destroying renderer");
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr) {
        INFO("Destroying window");
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    INFO("Quitting SDL");
    SDL_Quit();
}

void Application::Run() {

    while (!stop) {
        HandleEvents();
        world->Draw();
        SDL_Delay(100);
    }
}

void Application::HandleEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:  stop = true;
                            break;
            default:        break;
        }
    }
}

}   // namespace dwarfs
