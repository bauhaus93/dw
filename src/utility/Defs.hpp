/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <type_traits>

namespace dwarfs {

/* From https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int */
template <typename T>
constexpr auto ToUnderlying(T t) noexcept {
    return static_cast<std::underlying_type_t<T>>(t);
}

}   // namespace dwarfs
