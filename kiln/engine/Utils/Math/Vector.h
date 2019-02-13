#pragma once
#include <initializer_list>
#include <cmath>

namespace KMath {
  template<class T>
  class Vector {
  public:
    // Default constructor. Initializes components to zero.
    Vector() : x(0), y(0) {}
    // Component initialization constructor.
    Vector(T x, T y) : x(x), y(y) {}
    // Copy constructor.
    Vector(const Vector& vec) : x(vec.x), y(vec.y) {}

    T x, y;

    // Add instance components together with another vector's components.
    Vector operator+(const Vector& vec) const { return Vector(this->x + vec.x, this->y + vec.y); }
    Vector operator-(const Vector& vec) const { return Vector(this->x - vec.x, this->y - vec.y); }

    // Dot product of this instance with another vector.
    T dot(const Vector& vec) const { return this->x * vec.x + this->y * vec.y; }

    // Add scalar value to each component.
    template<class U>
    Vector operator+(const U& scalar) const { return Vector(this->x + scalar, this->y + scalar); }
    template<class U>
    Vector operator-(const U& scalar) const { return Vector(this->x - scalar, this->y - scalar); }

    // Multiply each component by a scalar.
    template<class U>
    Vector operator*(const U& scalar) const { return Vector(this->x * scalar, this->y * scalar); }
    template<class U>
    Vector operator/(const U& scalar) const { return Vector(this->x / scalar, this->y / scalar); }

    // Check vector equality. Non-int vectors should use 'equals' and supply a tolerance.
    bool operator==(const Vector& vec) const { return (this->x == vec.x) && (this->y == vec.y); };
    bool operator!=(const Vector& vec) const { return (this->x != vec.x) || (this->y != vec.y); };
    bool equals(const Vector& vec, float tolerance) { return (std::abs(this->x - vec.x) <= tolerance) && (std::abs(this->y - vec.y) <= tolerance); }

    // Check if a vector is zero. Non-int vectors should supply a tolerance.
    bool isZero() { return (this->x == 0.f) && (this->y == 0.f); }
    bool isZero(float tolerance) { return (std::abs(this->x) <= tolerance) && (std::abs(this->y) <= tolerance); }

    // Return the magnitude of the vector.
    float magnitude() { return std::sqrt(this->x*this->x + this->y*this->y); }

    Vector<float> normalize() {
      T mag = this->magnitude();
      return Vector(this->x / mag, this->y / mag);
    }
  };
};