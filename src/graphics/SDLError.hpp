/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <SDL.h>

#include "application/ApplicationError.hpp"

namespace dwarfs {

class SDLError: public ApplicationError {
 public:

    SDLError(const std::string& where);


};

}   // namespace dwarfs
