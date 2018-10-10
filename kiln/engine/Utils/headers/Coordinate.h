#pragma once

struct ICoordinate {
  int x = 0;
  int y = 0;

  inline ICoordinate add(const ICoordinate other) {
    return ICoordinate{this->x + other.x, this->y + other.y};
  }

  inline ICoordinate operator+(const ICoordinate other) {
    return this->add(other);
  }
};

struct FCoordinate {
  float x = 0;
  float y = 0;

  inline FCoordinate add(const FCoordinate other) {
    return FCoordinate{this->x + other.x, this->y + other.y};
  }

  inline FCoordinate operator+(const FCoordinate other) {
    return this->add(other);
  }
};