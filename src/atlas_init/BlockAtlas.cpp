/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "BlockAtlas.hpp"

namespace dwarfs {

static std::map<Material, uint32_t> LoadMaterialRows(const pugi::xml_node& atlasNode);
static ProtoBlockSet LoadPrototypes(SpriteAtlas& atlas, const pugi::xml_node& atlasNode, Point2i spriteSize);
static std::vector<Material> LoadBlockMaterials(pugi::xml_node& blockNode);
static std::map<Direction, uint32_t> LoadBlockCameraDirections(pugi::xml_node& blockNode);

ProtoBlockSet CreateBlockPrototypes(const std::string& xmlFile, SpriteAtlas& atlas, SDL_Renderer* renderer) {
    INFO("Creating block prototypes");
    pugi::xml_document doc;

    auto result = doc.load_file(xmlFile.c_str());
    if (!result) {
        throw ApplicationError("xml_document.load_file", result.description());
    }

    pugi::xml_node atlasListNode = doc.child("atlas_list");
    if (!atlasListNode) {
        pugi::xml_node dummyRoot;
        dummyRoot.set_name("root_dummy");
        throw XMLChildError("CreateBlockPrototypes", dummyRoot, "atlas_list");
    }

    pugi::xml_node atlasNode = atlasListNode.find_child_by_attribute("atlas", "name", "block-atlas");
    if (!atlasNode) {
        throw XMLChildError("CreateBlockPrototypes", atlasListNode, "atlas", "name", "block-atlas");
    }

    if (!atlasNode.attribute("output_name")) {
        throw XMLAttributeError("CreateBlockPrototypes", atlasNode, "output_name");
    }
    if (!atlasNode.attribute("element_width")) {
        throw XMLAttributeError("CreateBlockPrototypes", atlasNode, "element_width");
    }
    std::string atlasPath = atlasNode.attribute("output_name").value();
    int elementWidth = atlasNode.attribute("element_width").as_int();

    atlas.LoadImage(atlasPath, renderer);
    Point2i spriteSize { elementWidth, static_cast<int>(static_cast<float>(elementWidth) * SPRITE_RATIO) };
    INFO("Sprite sizes of atlas: ", spriteSize);
    if (spriteSize[0] != ATLAS_SPRITE_WIDTH) {
        WARN("Width of block sprites not equal to assumed ATLAS_SPRITE_WIDTH, Expected: ", ATLAS_SPRITE_WIDTH, ", Found: ", spriteSize[0]);
    }
    if (spriteSize[1] != ATLAS_SPRITE_HEIGHT) {
        WARN("Height of block sprites not equal to assumed ATLAS_SPRITE_HEIGHT, Expected: ", ATLAS_SPRITE_HEIGHT, ", Found: ", spriteSize[1]);
    }

    ProtoBlockSet prototypes = LoadPrototypes(atlas, atlasNode, spriteSize);

    INFO("Created ", prototypes.GetCount(), " block prototypes");
    return prototypes;
}

std::map<Material, uint32_t> LoadMaterialRows(const pugi::xml_node& atlasNode) {
    std::map<Material, uint32_t> materialRow;

    for (pugi::xml_node matProtNode = atlasNode.child("material_prototype");
         matProtNode;
         matProtNode = matProtNode.next_sibling("material_prototype")) {

        if (!matProtNode.attribute("type")) {
            throw XMLAttributeError("LoadMaterialRows", matProtNode, "type");
        }
        if (!matProtNode.attribute("row")) {
            throw XMLAttributeError("LoadMaterialRows", matProtNode, "row");
        }

        std::string typeStr = matProtNode.attribute("type").value();
        uint32_t row = static_cast<uint32_t>(matProtNode.attribute("row").as_int());
        Material type = GetMaterial(typeStr);
        materialRow.emplace(type, row);
    }
    return materialRow;
}

ProtoBlockSet LoadPrototypes(SpriteAtlas& atlas, const pugi::xml_node& atlasNode, Point2i spriteSize) {
    ProtoBlockSet prototypes;
    std::map<Material, uint32_t> materialRow = LoadMaterialRows(atlasNode);

    for (pugi::xml_node blockNode = atlasNode.child("block");
         blockNode;
         blockNode = blockNode.next_sibling("block")) {

        if (!blockNode.attribute("type")) {
            throw XMLAttributeError("LoadPrototypes", blockNode, "type");
        }
        std::string btStr = blockNode.attribute("type").value();
        BlockType blockType = GetBlockType(btStr);

        std::vector<Material> blockMats = LoadBlockMaterials(blockNode);
        std::map<Direction, uint32_t> camColumn = LoadBlockCameraDirections(blockNode);

        for (Material mat: blockMats) {
            uint32_t row = materialRow.at(mat);
            for (const auto& iter: camColumn) {
                uint32_t col = iter.second;
                RectI spriteRect { spriteSize[0] * static_cast<int>(col), spriteSize[1] * static_cast<int>(row), spriteSize[0], spriteSize[1] };
                Sprite sprite { spriteRect, atlas };
                std::shared_ptr<Block> block = nullptr;
                switch(blockType) {
                    case BlockType::CUBE:       block = std::make_shared<Cube>(sprite, mat);                break;
                    case BlockType::SLOPE:      block = std::make_shared<Slope>(sprite, mat, iter.first);   break;
                    case BlockType::FLOOR:      block = std::make_shared<Floor>(sprite, mat);               break;
                    case BlockType::SELECTION:  block = std::make_shared<Selection>(sprite, mat);           break;
                    default:    assert(0);  break;
                }
                if (block != nullptr) {
                    prototypes.AddBlock(block);
                }
             }
        }
    }
    return prototypes;
}

std::vector<Material> LoadBlockMaterials(pugi::xml_node& blockNode) {
    std::vector<Material> matTypes;
    for (pugi::xml_node matNode = blockNode.child("material");
            matNode;
            matNode = matNode.next_sibling("material")) {
        if (!matNode.attribute("type")) {
            throw XMLAttributeError("LoadMaterialsForBlock", matNode, "type");
        }
        std::string mtStr = matNode.attribute("type").value();
        matTypes.push_back(GetMaterial(mtStr));
    }
    return matTypes;
}

std::map<Direction, uint32_t> LoadBlockCameraDirections(pugi::xml_node& blockNode) {
    std::map<Direction, uint32_t> cameraRow;
    for (pugi::xml_node camNode = blockNode.child("camera");
            camNode;
            camNode = camNode.next_sibling("camera")) {
        if (!camNode.attribute("angle_id")) {
            throw XMLAttributeError("LoadBlockCameraDirections", camNode, "angle_id");
        }
        if (!camNode.attribute("column")) {
            throw XMLAttributeError("LoadBlockCameraDirections", camNode, "column");
        }
        int angleId = camNode.attribute("angle_id").as_int();
        Direction dir = GetDirectionByAngleId(angleId);
        uint32_t column = static_cast<uint32_t>(camNode.attribute("column").as_int());
        cameraRow.emplace(dir, column);
    }
    return cameraRow;
}

}   // namespace dwarfs

