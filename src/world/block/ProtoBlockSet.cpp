/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "ProtoBlockSet.hpp"

namespace dwarfs {

void ProtoBlockSet::AddBlock(std::shared_ptr<Block> prototype) {
    auto result = prototypes.insert(prototype);
    if (result.second == false) {
        const auto& existing = result.first;
        WARN("Tried to insert duplicate block prototype: Added block: ", *prototype, ", existing block: ", *existing);
    }
}

std::shared_ptr<const Block> ProtoBlockSet::GetPrototype(Material material, BlockType type) const {
    static const SpriteAtlas dummyAtlas;
    static const Sprite dummySprite(RectI(0, 0, 0, 0), dummyAtlas);

    auto b = std::make_shared<Block>(dummySprite, material, type);
    auto find = prototypes.find(b);
    assert(find != prototypes.end());
    return *find;
}

std::shared_ptr<const DirectionalBlock> ProtoBlockSet::GetPrototype(Material material, BlockType type, Direction dir) const {
    static const SpriteAtlas dummyAtlas;
    static const Sprite dummySprite(RectI(0, 0, 0, 0), dummyAtlas);

    auto b = std::make_shared<DirectionalBlock>(dummySprite, material, type, dir);
    auto find = prototypes.find(b);
    assert(find != prototypes.end());
    return std::static_pointer_cast<const DirectionalBlock>(*find);
}

}   // namespace dwarfs
