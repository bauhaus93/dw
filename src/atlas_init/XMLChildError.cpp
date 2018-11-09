/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "XMLChildError.hpp"

namespace dwarfs {

XMLChildError::XMLChildError(
    const std::string& where,
    const pugi::xml_node node,
    const std::string& childname):
    ApplicationError("XMLChildError", where, std::string("Node '") + node.name() + "' has no child '" + childname + "'") {

}

XMLChildError::XMLChildError(
    const std::string& where,
    const pugi::xml_node& node,
    const std::string& childName,
    const std::string& attributeName,
    const std::string& attributeValue):
    ApplicationError("XMLAttributeError", where, std::string("Node '") + node.name() + "' has no child '" + childName + "' with attribute '" + attributeName + "' of value '" + attributeValue + "'") {
}



}   // namespace dwarfs
