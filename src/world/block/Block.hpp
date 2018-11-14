/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <SDL.h>

#include "utility/Defs.hpp"
#include "graphics/Sprite.hpp"
#include "Material.hpp"
#include "BlockType.hpp"

namespace dwarfs {

class Block {
public:
                        Block(Sprite sprite_, Material material_, BlockType type_);
    virtual             ~Block() = default;
    void                Draw(const Point2i dest, SDL_Renderer* renderer) const;
    Material            GetMaterial() const { return material; }
    BlockType           GetType() const { return type; }
    virtual int         CalculateId() const;
    virtual std::string GetString() const;
private:
    Sprite          sprite;
    Material        material;
    BlockType       type;

};

inline bool operator<(const Block& rhs, const Block& lhs) {
    return  rhs.CalculateId() < lhs.CalculateId();
}

std::ostream& operator<<(std::ostream& os, const Block& block);

}   // namespace dwarfs
