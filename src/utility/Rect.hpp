/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <iostream>

#include "Point2.hpp"

namespace dwarfs {

template<typename T>
class Rect {
public:
                            Rect(T originX, T originY, T sizeX, T sizeY);
                            Rect(const Point2<T>& origin_, const Point2<T>& size_);
    const Point2<T>&        GetOrigin() const { return origin; }
    const Point2<T>&        GetSize() const { return size; }
    bool                    InBoundaryX(const Point2<T>& point) const;
    bool                    InBoundaryY(const Point2<T>& point) const;
    bool                    InBoundaries(const Point2<T>& point) const;
    bool                    InBoundaries(const Point2<T>& point, const Point2<T>& tolerance) const;
    bool                    InBoundaries(const Rect<T>& other) const;
    T&                      operator[](uint8_t index);
    const T&                operator[](uint8_t index) const;

private:
    Point2<T>     origin;
    Point2<T>     size;
};

typedef Rect<int8_t> Rect8i;
typedef Rect<uint8_t> Rect8u;
typedef Rect<int32_t> Rect32i;
typedef Rect<uint32_t> Rect32u;
typedef Rect32i RectI;
typedef Rect32u RectU;

template<typename T>
Rect<T>::Rect(T originX, T originY, T sizeX, T sizeY):
    origin { Point2<T> { originX, originY } },
    size { Point2<T> { sizeX, sizeY } } {
}

template<typename T>
Rect<T>::Rect(const Point2<T>& origin_, const Point2<T>& size_):
    origin { origin_ },
    size { size_ } {
}

template<typename T>
bool Rect<T>::InBoundaryX(const Point2<T>& point) const {
    return point[0] >= origin[0] &&
           point[0] <= origin[0] + size[0];
}

template<typename T>
bool Rect<T>::InBoundaryY(const Point2<T>& point) const {
    return point[1] >= origin[1] &&
           point[1] <= origin[1] + size[1];
}

template<typename T>
bool Rect<T>::InBoundaries(const Point2<T>& point) const {
    return InBoundaryX(point) && InBoundaryY(point);
}

template<typename T>
bool Rect<T>::InBoundaries(const Point2<T>& point, const Point2<T>& tolerance) const {
    if (point[0] >= origin[0] &&
        point[1] >= origin[1] &&
        point[0] <= origin[0] + size[0] &&
        point[1] <= origin[1] + size[1]) {
        return true;
    }
    return point[0] + tolerance[0] >= origin[0] &&
           point[1] + tolerance[1] >= origin[1] &&
           point[0] - tolerance[0] <= origin[0] + size[0] &&
           point[1] - tolerance[1] <= origin[1] + size[1];
}

template<typename T>
bool Rect<T>::InBoundaries(const Rect<T>& other) const {
    return InBoundaries(other.origin) &&
           InBoundaries(other.origin + other.size);
}

template<typename T>
T& Rect<T>::operator[](uint8_t index) {
    if (index < 2) {
        return origin[index];
    } else {
        return size[index % 2];
    }
}

template<typename T>
const T& Rect<T>::operator[](uint8_t index) const {
    if (index < 2) {
        return origin[index];
    } else {
        return size[index % 2];
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect) {
    os.operator<<(rect[0]);
    for (int i = 1; i < 4; i++) {
        os << "/";
        os.operator<<(rect[i]);
    }
    return os;
}

}       // namespace dwarfs
