/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Application.hpp"

namespace dwarfs {

Application::Application(int winSizeX, int winSizeY):
    stop { false },
    window { nullptr },
    windowRect { 0, 0, winSizeX, winSizeY },
    windowCenter { winSizeX / 2, winSizeY / 2 },
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
        windowRect[2],
        windowRect[3],
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
    INFO("Drawing loaded sprites");
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    world->DrawSpriteAtlas(windowRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    world->CenterCamera(Point2i { 0, 0 }, windowCenter);

    INFO("Starting main loop");
    uint32_t updateTime = 0;
    uint32_t lastPrint = SDL_GetTicks();
    uint32_t ticks = 0;
    while (!stop) {
        uint32_t start = SDL_GetTicks();
        Update();
        updateTime += SDL_GetTicks() - start;
        ticks++;
        uint32_t diff = SDL_GetTicks() - lastPrint;
        if (diff >= 1000) {
            DEBUG("Avg update time: ", updateTime / ticks, "ms");
            updateTime = 0;
            ticks = 0;
            lastPrint = SDL_GetTicks();
        }
        SDL_Delay(100);
    }
    INFO("Stopping main loop");
}

void Application::Update() {
    HandleEvents();
    Draw();
}

void Application::Draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    world->Draw(windowRect);
    /*SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 0, 0, windowRect[2], windowRect[3]);
    SDL_RenderDrawLine(renderer, windowRect[2], 0, 0, windowRect[3]);*/
    SDL_RenderPresent(renderer);
}

void Application::HandleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:  stop = true;
                            break;
            case SDL_MOUSEBUTTONUP:
                            HandleMouseButtonEvent(event.button);
                            break;

            default:        break;
        }
    }
}

void Application::HandleMouseButtonEvent(const SDL_MouseButtonEvent& event) {
    switch(event.type) {
        case SDL_MOUSEBUTTONUP:
            if (event.button == SDL_BUTTON_LEFT) {
                world->SetCameraByScreenPos(Point2i { event.x - windowRect[2] / 2, event.y - windowRect[3] / 2 });
            }
            break;
        default:    break;   
    }
}

}   // namespace dwarfs
