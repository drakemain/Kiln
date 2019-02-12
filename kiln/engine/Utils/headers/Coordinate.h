#pragma once

struct FCoordinate;

struct ICoordinate {
  int x = 0;
  int y = 0;

  inline ICoordinate add(const ICoordinate other) const {
    return ICoordinate{this->x + other.x, this->y + other.y};
  }

  inline ICoordinate operator+(const ICoordinate other) const {
    return this->add(other);
  }
};

struct FCoordinate {
  float x = 0;
  float y = 0;

  inline FCoordinate add(const FCoordinate other) const {
    return FCoordinate{this->x + other.x, this->y + other.y};
  }

  inline FCoordinate operator+(const FCoordinate other) const {
    return this->add(other);
  }

  static inline FCoordinate fromInt(const ICoordinate& other) {
    FCoordinate res;
    res.x = (float)other.x;
    res.y = (float)other.y;
    return res;
  }
};