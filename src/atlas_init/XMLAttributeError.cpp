/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "XMLAttributeError.hpp"

namespace dwarfs {

XMLAttributeError::XMLAttributeError(
    const std::string& where,
    const pugi::xml_node& node,
    const std::string& attributeName):
    ApplicationError("XMLAttributeError", where, std::string("Node '") + node.name() + "' has no attribute '" + attributeName + "'") {
}

}   // namespace dwarfs
