/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>
#include <string>

namespace dwarfs {

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

const char* GetString(Direction dir);
Direction GetDirection(const std::string& str);
Direction GetDirectionByAngleId(int angleId);

}   // namespace dwarfs