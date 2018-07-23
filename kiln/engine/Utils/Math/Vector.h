#pragma once
#include <initializer_list>
#include <cmath>

namespace KMath {
  template<class T>
  class Vector {
  public:
    Vector() : x(0), y(0) {}
    Vector(T x, T y) : x(x), y(y) {}
    Vector(const Vector& vec) : x(vec.x), y(vec.y) {}

    T x, y;

    Vector operator+(const Vector& vec) const { return Vector(this->x + vec.x, this->y + vec.y); }
    Vector operator-(const Vector& vec) const { return Vector(this->x - vec.x, this->y - vec.y); }
    T dot(const Vector& vec) const { return this->x * vec.x + this->y * vec.y; }

    template<class U>
    Vector operator+(const U& scalar) const { return Vector(this->x + scalar, this->y + scalar); }
    template<class U>
    Vector operator-(const U& scalar) const { return Vector(this->x - scalar, this->y - scalar); }
    template<class U>
    Vector operator*(const U& scalar) const { return Vector(this->x * scalar, this->y * scalar); }
    template<class U>
    Vector operator/(const U& scalar) const { return Vector(this->x / scalar, this->y / scalar); }

    bool operator==(const Vector& vec) const { return (this->x == vec.x) && (this->y == vec.y); };
    bool operator!=(const Vector& vec) const { return (this->x != vec.x) || (this->y != vec.y); };
    bool equals(const Vector& vec, float tolerance) { return (std::abs(this->x - vec.x) <= tolerance) && (std::abs(this->y - vec.y) <= tolerance); }
  };
};