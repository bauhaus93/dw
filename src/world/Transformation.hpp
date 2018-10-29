/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <cstdint>

#include "utility/Point2.hpp"
#include "AtlasFormat.hpp"

namespace dwarfs {

Point2i WorldToScreenPos(const Point2i& worldPos, const Point2i& origin);
Point2i ScreenToWorldPos(const Point2i& screenPos, const Point2i& origin);

}   // namespace dwarfs
