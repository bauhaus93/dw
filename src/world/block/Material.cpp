/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Material.hpp"

namespace dwarfs {

const char* GetString(Material mt) {
    switch (mt) {
        case Material::GRASS:   return "GRASS";
        case Material::ROCK:    return "ROCK";    
        case Material::MUD:     return "MUD";
        default:                    return "UNKNOWN";
    }
}

Material GetMaterial(const std::string& str) {
    if (str == "GRASS") {
        return Material::GRASS;
    } else if (str == "ROCK") {
        return Material::ROCK;
    } else if (str == "MUD") {
        return Material::MUD;
    }
    assert(0);
    throw;
}




}   // namespace dwarfs