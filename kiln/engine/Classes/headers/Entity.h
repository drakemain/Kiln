#pragma once
#include "kiln/engine/Utils/headers/Coordinate.h"

// Entities are objects that have
// a position within the game
class Entity {
public:
  Entity();
  virtual ~Entity();

  Coordinate getWorldPosition() const;
  void setWorldPosition(int x, int y);
  void setWorldPosition(Coordinate position);

  virtual void centerInWindow(unsigned int xBoundary, unsigned int yBoundary);

  virtual void tick(float deltaTime) = 0;
private:
  Coordinate worldPosition;
};