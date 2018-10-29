/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Transformation.hpp"

namespace dwarfs {

constexpr float WIDTH = static_cast<float>(TILE_WIDTH);
constexpr float HEIGHT = static_cast<float>(TILE_HEIGHT);
constexpr float HEIGHT_CORRECTION = 1.125f;

Point2i WorldToScreenPos(const Point2i& worldPos, const Point2i& origin) {
    Point2f pos = worldPos - origin;
    return Point2i { static_cast<int32_t>(((pos[0] - pos[1]) * WIDTH * 0.5) + 0.5),
                     static_cast<int32_t>(((pos[0] + pos[1]) * HEIGHT * 0.5 * HEIGHT_CORRECTION) + 0.5) };
}

Point2i WorldToScreenPos(const Point3i& worldPos, const Point3i& origin) {
    Point3f pos = worldPos - origin;
    return Point2i { static_cast<int32_t>(((pos[0] - pos[1]) * WIDTH * 0.5) + 0.5),
                     static_cast<int32_t>(((pos[0] + pos[1] - 2 * pos[2]) * HEIGHT * 0.5 * HEIGHT_CORRECTION) + 0.5) };
}

Point2i ScreenToWorldPos(const Point2i& screenPos, const Point2i& origin) {
    float u = (screenPos[0] / (WIDTH * 0.5) + screenPos[1] / (HEIGHT * 0.5 * HEIGHT_CORRECTION)) * 0.5;
    float v = u - screenPos[0] / (WIDTH * 0.5);
    return Point2i { static_cast<int32_t>(u + 0.5) + origin[0],
                     static_cast<int32_t>(v + 0.5) + origin[1] };
}

}   // namespace dwarfs