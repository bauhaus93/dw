/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Direction.hpp"

namespace dwarfs {

const char* GetString(Direction dir) {
    switch (dir) {
        case Direction::NORTH:  return "NORTH";
        case Direction::EAST:   return "EAST";    
        case Direction::SOUTH:  return "SOUTH";
        case Direction::WEST:   return "WEST";
        default:                return "UNKNOWN";
    }
}

Direction GetDirection(const std::string& str) {
    if (str == "NORTH") {
        return Direction::NORTH;
    } else if (str == "EAST") {
        return Direction::EAST;
    } else if (str == "SOUTH") {
        return Direction::SOUTH;
    } else if (str == "WEST") {
        return Direction::WEST;
    }
    assert(0);
    throw;
}

Direction GetDirectionByAngleId(int angleId) {
    switch (angleId) {
        case 0: return Direction::NORTH;
        case 1: return Direction::EAST;
        case 2: return Direction::SOUTH;
        case 3: return Direction::WEST;
        default:    assert(0);
    }
    throw;
}

std::ostream& operator<<(std::ostream& os, const Direction& dir) {
    os << GetString(dir);
    return os;
}

}   // namespace dwarfs