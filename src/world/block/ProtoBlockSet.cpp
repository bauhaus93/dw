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
    int id = Block::CalculateId(material, type);
    auto find = std::find_if(
        prototypes.begin(),
        prototypes.end(),
        [id](const std::shared_ptr<Block>& block) {
            return block->CalculateId() == id;
        });
    assert(find != prototypes.end());
    return *find;
}

std::shared_ptr<const DirectionalBlock> ProtoBlockSet::GetPrototype(Material material, BlockType type, Direction dir) const {
    int id = DirectionalBlock::CalculateId(material, type, dir);
    auto find = std::find_if(
        prototypes.begin(),
        prototypes.end(),
        [id](const std::shared_ptr<Block>& block) {
            return block->CalculateId() == id;
        });
    assert(find != prototypes.end());
    return std::static_pointer_cast<const DirectionalBlock>(*find);
}

}   // namespace dwarfs
