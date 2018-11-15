/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Material.hpp"

namespace dwarfs {

const char* GetString(Material mat) {
    switch (mat) {
        case Material::GRASS:   return "GRASS";
        case Material::ROCK:    return "ROCK";    
        case Material::MUD:     return "MUD";
        case Material::WHITE:   return "WHITE";
        default:                return "UNKNOWN";
    }
}

Material GetMaterial(const std::string& str) {
    if (str == "GRASS") {
        return Material::GRASS;
    } else if (str == "ROCK") {
        return Material::ROCK;
    } else if (str == "MUD") {
        return Material::MUD;
    } else if (str == "WHITE") {
        return Material::WHITE;
    }
    assert(0);
    throw;
}

std::ostream& operator<<(std::ostream& os, const Material& mat) {
    os << GetString(mat);
    return os;
}




}   // namespace dwarfs