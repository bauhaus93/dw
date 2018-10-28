/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "SDLError.hpp"

namespace dwarfs {

SDLError::SDLError(const std::string& where):
    ApplicationError("SDLError", where, std::string(SDL_GetError())) {
}



}   // namespace dwarfs
