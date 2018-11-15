/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Volume.hpp"

namespace dwarfs {

Volume::Volume(std::shared_ptr<const Block> block_, std::shared_ptr<const Floor> floor_):
    block { block_ },
    floor { floor_ } {
}

Volume::Volume(std::shared_ptr<const Floor> floor_):
    block { nullptr },
    floor { floor_ } {
}

void Volume::Draw(const Point2i& dest, SDL_Renderer* renderer) {
    if (floor != nullptr) {
        floor->Draw(dest, renderer);
    }
    if (block != nullptr) {
        block->Draw(dest + Point2i(0, -5), renderer);
    }   
}

}   // namespace dwarfs