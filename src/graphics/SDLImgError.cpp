/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "SDLImgError.hpp"

namespace dwarfs {

SDLImgError::SDLImgError(const std::string& where):
    ApplicationError("SDLImgError", where, std::string(IMG_GetError())) {
}



}   // namespace dwarfs
