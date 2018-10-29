/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Transformation.hpp"

namespace dwarfs {

Point2i WorldToScreenPos(const Point2i& worldPos, const Point2i& center) {
    constexpr float WIDTH = static_cast<float>(atlas_format::SPRITE_WIDTH);
    Point2f pos = worldPos - center;
    return Point2i { static_cast<int32_t>(((pos[0] - pos[1]) * WIDTH * 0.5) + 0.5),
                     static_cast<int32_t>(((pos[0] + pos[1]) * WIDTH * 0.28) + 0.5) };
}

Point2i ScreenToWorldPos(const Point2i& screenPos, const Point2i& center) {
    constexpr float WIDTH = static_cast<float>(atlas_format::SPRITE_WIDTH);
    float u = (screenPos[0] / (WIDTH * 0.5) + screenPos[1] / (WIDTH * 0.28)) * 0.5;
    float v = u - screenPos[0] / (WIDTH * 0.5);
    return Point2i { static_cast<int32_t>(u + 0.5) + center[0],
                     static_cast<int32_t>(v + 0.5) + center[1] };
}

}   // namespace dwarfs