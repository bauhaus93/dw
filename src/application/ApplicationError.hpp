/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <stdexcept>
#include <string>
#include <sstream>

namespace dwarfs {

class ApplicationError: public std::runtime_error {
 public:

    ApplicationError(const std::string& name,
                        const std::string& where,
                        const std::string& description);



};

}   // namespace dwarfs
