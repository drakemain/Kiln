#pragma once
#include "kiln/engine/Utils/headers/Coordinate.h"
#include <vector>

// Entities are objects that have
// a position within the game
class Entity {
public:
  Entity();
  virtual ~Entity();

  FCoordinate getWorldPosition() const;
  void setWorldPosition(float x, float y);
  void setWorldPosition(FCoordinate position);

  void bindComponent(class EntityComponent* component);

  void updateComponentPositions();

  virtual void centerInWindow(unsigned int xBoundary, unsigned int yBoundary);

private:
  FCoordinate worldPosition;
  std::vector<class EntityComponent*> boundComponents;
};