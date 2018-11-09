/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "MaterialType.hpp"

namespace dwarfs {

const char* GetString(MaterialType mt) {
    switch (mt) {
        case MaterialType::GRASS:   return "GRASS";
        case MaterialType::ROCK:    return "ROCK";    
        case MaterialType::MUD:     return "MUD";
        default:                    return "UNKNOWN";
    }
}

MaterialType GetMaterial(const std::string& str) {
    if (str == "GRASS") {
        return MaterialType::GRASS;
    } else if (str == "ROCK") {
        return MaterialType::ROCK;
    } else if (str == "MUD") {
        return MaterialType::MUD;
    }
    assert(0);
}




}   // namespace dwarfs