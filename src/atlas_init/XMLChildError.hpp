/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>

#include <pugixml.hpp>

#include "application/ApplicationError.hpp"

namespace dwarfs {

class XMLChildError: public ApplicationError {
 public:
    XMLChildError(const std::string& where,
                  const pugi::xml_node node,
                  const std::string& childname);
    XMLChildError(const std::string& where,
                  const pugi::xml_node& node,
                  const std::string& childName,
                  const std::string& attributeName,
                  const std::string& attributeValue);

};

}   // namespace dwarfs
