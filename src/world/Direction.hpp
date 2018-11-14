/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>
#include <string>
#include <iostream>

namespace dwarfs {

constexpr int DIRECTION_COUNT = 4;

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

const char* GetString(Direction dir);
Direction GetDirection(const std::string& str);
Direction GetDirectionByAngleId(int angleId);

std::ostream& operator<<(std::ostream& os, const Direction& dir);

}   // namespace dwarfs