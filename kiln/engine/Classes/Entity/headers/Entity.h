#pragma once
#include "kiln/engine/Utils/headers/Coordinate.h"
#include <vector>

struct SDL_Renderer;

// Entities are objects that have
// a position within the game
class Entity {

public:
  Entity();
  virtual ~Entity();

  virtual void tick(float deltaTime);
  virtual void start();

  ICoordinate getWorldPosition() const;

  void setWorldPosition(float x, float y);
  void setWorldPosition(ICoordinate position);

  virtual void scale(float);

  void bindComponent(class Component* component);
  void unbindComponent(class Component* component);

  virtual void centerInWindow(unsigned int xBoundary, unsigned int yBoundary);

  virtual void render(SDL_Renderer* renderer);

  std::vector<class Component*> getComponents();

private:
  void updateComponentPositions();

  ICoordinate worldPosition;
  std::vector<class Component*> boundComponents;
};