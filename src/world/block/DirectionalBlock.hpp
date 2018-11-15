/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "graphics/Sprite.hpp"
#include "world/Direction.hpp"
#include "Block.hpp"
#include "Material.hpp"

namespace dwarfs {

class DirectionalBlock: public Block {
public:
                        DirectionalBlock(Sprite sprite_, Material material_, BlockType type_, Direction dir_);
    virtual            ~DirectionalBlock() = default;
    Direction           GetDirection() const { return direction; }
    int                 CalculateId() const override;
    static int          CalculateId(Material mat, BlockType type, Direction dir);
    std::string         GetString() const override;

private:
    Direction           direction;

};


}   // namespace dwarfs
