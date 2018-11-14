/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cassert>
#include <string>

namespace dwarfs {

constexpr int BLOCKTYPE_COUNT = 3;

enum class BlockType {
    CUBE,
    SLOPE,
    FLOOR
};

const char* GetString(BlockType bt);
BlockType GetBlockType(const std::string& str);

}   // namespace dwarfs