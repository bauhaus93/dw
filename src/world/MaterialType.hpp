/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>

namespace dwarfs {

enum class MaterialType {
    GRASS,
    ROCK,
    MUD
};

inline int GetValue(const MaterialType& mt) {
    switch (mt) {
        case MaterialType::GRASS:   return 0;
        case MaterialType::ROCK:    return 1;
        case MaterialType::MUD:     return 2;
        default:                    assert(0);
    }
}

/*inline bool operator<(const MaterialType& lhs, const MaterialType& rhs) {
    return GetValue(lhs) < GetValue(rhs);
}*/




}   // namespace dwarfs
