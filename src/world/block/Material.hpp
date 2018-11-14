/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>
#include <string>

namespace dwarfs {

constexpr int MATERIAL_COUNT = 3;

enum class Material {
    GRASS,
    ROCK,
    MUD
};

const char* GetString(Material mt);
Material GetMaterial(const std::string& str);

}   // namespace dwarfs
