/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Transformation.hpp"

namespace dwarfs {

constexpr float WIDTH = static_cast<float>(TILE_WIDTH);
constexpr float WIDTH_HALF = static_cast<float>(TILE_WIDTH / 2);
constexpr float HEIGHT = static_cast<float>(TILE_HEIGHT);

Point2i WorldToScreenPos(const Point2i& worldPos, const Point2i& origin) {
    Point2f pos = worldPos - origin;
    return Point2i { static_cast<int32_t>(((pos[0] - pos[1]) * WIDTH * 0.5) + 0.5),
                     static_cast<int32_t>(((pos[0] + pos[1]) * HEIGHT * 0.5) + 0.5) };
}

Point2i WorldToScreenPos(const Point3i& worldPos, const Point3i& origin) {
    Point3i pos = worldPos - origin;
    return Point2i { (pos[0] - pos[1]) * TILE_WIDTH / 2,
                     (pos[0] + pos[1] - 2 * pos[2]) * TILE_HEIGHT / 2 };
}

Point2i ScreenToWorldPos(const Point2i& screenPos, const Point2i& origin) {
    int32_t u = (screenPos[0] / (TILE_WIDTH / 2) + screenPos[1] / (TILE_HEIGHT / 2)) / 2;
    int32_t v = u - screenPos[0] / (TILE_WIDTH / 2);
    return Point2i { u + origin[0],
                     v + origin[1] };
}

}   // namespace dwarfs