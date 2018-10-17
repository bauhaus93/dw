/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "ApplicationError.hpp"

namespace dwarfs {

ApplicationError::ApplicationError(const std::string& name,
                                   const std::string& where,
                                   const std::string& description):
    std::runtime_error(name + " @ " + where + ": " + description) {

}



}   // namespace dwarfs
