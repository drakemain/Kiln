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

  FCoordinate getWorldPosition() const;

  void setWorldPosition(float x, float y);
  void setWorldPosition(FCoordinate position);

  virtual void scale(float);

  void bindComponent(class Component* component);
  void unbindComponent(class Component* component);

  virtual void centerInWindow(unsigned int xBoundary, unsigned int yBoundary);

  virtual void render(SDL_Renderer* renderer);

  void getComponents(std::vector<class Component*>& components) const;

private:
  void updateComponentPositions();

  FCoordinate worldPosition;
  std::vector<class Component*> boundComponents;

public:
  // Inline so that all possible headers don't 
  // need to be included in this file
  template <class T>
  inline void getComponentsByType(std::vector<T>& components) const {
    for (Component* comp : this->boundComponents) {
      T castComp = dynamic_cast<T>(comp);

      if (castComp) {
        components.push_back(castComp);
      }
    }
  }
};