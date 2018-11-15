/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Transformation.hpp"

namespace dwarfs {

Point2i WorldToScreenPos(const Point2i& worldPos, const Point2i& origin) {
    Point2i pos = worldPos - origin;
    return Point2i { ((pos[0] - pos[1]) * TILE_WIDTH) / 2,
                     ((pos[0] + pos[1]) * TILE_HEIGHT) / 2 };
}

Point2i WorldToScreenPos(const Point3i& worldPos, const Point3i& origin) {
    Point3i pos = worldPos - origin;
    return Point2i { (pos[0] - pos[1]) * TILE_WIDTH / 2,
                     (pos[0] + pos[1] - 3 * pos[2]) * TILE_HEIGHT / 2 + 3 * pos[2] };
}

Point2i ScreenToWorldPos(const Point2i& screenPos, const Point2i& origin) {
    int32_t u = (screenPos[0] / (TILE_WIDTH / 2) + screenPos[1] / (TILE_HEIGHT / 2)) / 2;
    int32_t v = u - screenPos[0] / (TILE_WIDTH / 2);
    return Point2i { u + origin[0],
                     v + origin[1] };
}

}   // namespace dwarfs