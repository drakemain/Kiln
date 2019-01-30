#pragma once
#include "kiln/engine/Utils/headers/Coordinate.h"
#include <vector>
#include <SDL_render.h>

// Entities are objects that have
// a position within the game
class Entity {
public:
  Entity();
  virtual ~Entity();

  virtual void tick(float deltaTime) = 0;
  virtual void start() = 0;

  ICoordinate getWorldPosition() const;

  void setWorldPosition(float x, float y);
  void setWorldPosition(ICoordinate position);

  void bindComponent(class Component* component);

  virtual void centerInWindow(unsigned int xBoundary, unsigned int yBoundary);

  virtual void render(SDL_Renderer* renderer);

protected:
  std::vector<class Component*> getComponents();

private:
  void updateComponentPositions();

  ICoordinate worldPosition;
  std::vector<class Component*> boundComponents;
};