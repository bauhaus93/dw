/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>

#include <SDL2/SDL_image.h>

#include "application/ApplicationError.hpp"

namespace dwarfs {

class SDLImgError: public ApplicationError {
 public:

    SDLImgError(const std::string& where);


};

}   // namespace dwarfs
