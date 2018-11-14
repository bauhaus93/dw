/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <memory>

#include <SDL.h>

#include "utility/Point2.hpp"
#include "Block.hpp"
#include "Floor.hpp"

namespace dwarfs {

class Volume {
public:
                    Volume(std::shared_ptr<const Block> block_, std::shared_ptr<const Floor> floor_);
    explicit        Volume(std::shared_ptr<const Floor> floor_);
    void            Draw(const Point2i& dest, SDL_Renderer* renderer);

private:
    std::shared_ptr<const Block>  block;
    std::shared_ptr<const Floor>  floor;
};


}   // namespace dwarfs
