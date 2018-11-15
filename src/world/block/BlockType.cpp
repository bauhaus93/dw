/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "BlockType.hpp"

namespace dwarfs {

const char* GetString(BlockType mt) {
    switch (mt) {
        case BlockType::CUBE:   return "CUBE";
        case BlockType::SLOPE:  return "SLOPE";    
        case BlockType::FLOOR:  return "FLOOR";
        default:                return "UNKNOWN";
    }
}

BlockType GetBlockType(const std::string& str) {
    if (str == "CUBE") {
        return BlockType::CUBE;
    } else if (str == "SLOPE") {
        return BlockType::SLOPE;
    } else if (str == "FLOOR") {
        return BlockType::FLOOR;
    } else if (str == "SELECTION") {
        return BlockType::SELECTION;
    }
    assert(0);
    throw;
}

std::ostream& operator<<(std::ostream& os, const BlockType& type) {
    os << GetString(type);
    return os;
}


}   // namespace dwarfs