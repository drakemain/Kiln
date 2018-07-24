#pragma once
#include "kiln/engine/Utils/headers/Coordinate.h"

// Entities are objects that have
// a position within the game
class Entity {
public:
  Entity();
  virtual ~Entity();

  FCoordinate getWorldPosition() const;
  void setWorldPosition(float x, float y);
  void setWorldPosition(FCoordinate position);

  virtual void centerInWindow(unsigned int xBoundary, unsigned int yBoundary);
private:
  FCoordinate worldPosition;
};