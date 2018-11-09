/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <string>

#include <pugixml.hpp>

#include "application/ApplicationError.hpp"

namespace dwarfs {

class XMLAttributeError: public ApplicationError {
 public:
    XMLAttributeError(const std::string& where,
                      const pugi::xml_node& node,
                      const std::string& attributeName);
};

}   // namespace dwarfs
