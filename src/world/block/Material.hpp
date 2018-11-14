/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <iostream>
#include <cassert>
#include <string>

namespace dwarfs {

constexpr int MATERIAL_COUNT = 3;

enum class Material {
    GRASS,
    ROCK,
    MUD
};

const char* GetString(Material mat);
Material GetMaterial(const std::string& str);

std::ostream& operator<<(std::ostream& os, const Material& mat);

}   // namespace dwarfs
