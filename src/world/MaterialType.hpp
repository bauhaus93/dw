/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>
#include <string>

namespace dwarfs {

enum class MaterialType {
    GRASS,
    ROCK,
    MUD
};

const char* GetString(MaterialType mt);
MaterialType GetMaterial(const std::string& str);

}   // namespace dwarfs
