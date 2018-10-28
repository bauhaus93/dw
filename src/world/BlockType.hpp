/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>

namespace dwarfs {

enum class BlockType {
    CUBE,
    SLOPE
};

inline int GetValue(const BlockType& bt) {
    switch (bt) {
        case BlockType::CUBE:   return 0;
        case BlockType::SLOPE:  return 1;
        default:                assert(0);
    }
}

/*inline bool operator<(const BlockType& lhs, const BlockType& rhs) {
    return GetValue(lhs) < GetValue(rhs);
}*/



}   // namespace dwarfs
