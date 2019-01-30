#include "../headers/Entity.h"
#include <iostream>
#include <kiln/engine/Classes/headers/Entity.h>
#include "../Components/headers/SpriteComponent.h"


Entity::Entity() {}
Entity::~Entity() {}

ICoordinate Entity::getWorldPosition() const {
  return this->worldPosition;
}

void Entity::setWorldPosition(float x, float y) {
  this->worldPosition.x = x;
  this->worldPosition.y = y;

  this->updateComponentPositions();
}

void Entity::setWorldPosition(ICoordinate position) {
  std::cout << "Modifying entity position" << std::endl;
  std::cout << "\t{" << position.x << ", " << position.y << "}" << std::endl;
  
  this->worldPosition = position;
  this->updateComponentPositions();
}

void Entity::bindComponent(Component* component) {
  std::cout << "Binding component" << std::endl;
  
  for (Component* comp : this->boundComponents) {
    if (component == comp) {
      return;
    }
  }

  this->boundComponents.push_back(component);
}

void Entity::render(SDL_Renderer *renderer) {
  for (Component* comp : this->boundComponents) {
    SpriteComponent* sprite = dynamic_cast<SpriteComponent*>(comp);

    if (sprite) {
      sprite->render(renderer);
    }
  }
}

void Entity::updateComponentPositions() {
  for (Component* comp : this->boundComponents) {
    std::cout << "\tUpdating component." << std::endl;
    comp->updatePosition();
  }
}

void Entity::centerInWindow(unsigned int xBoundary, unsigned int yBoundary) {
  this->setWorldPosition(xBoundary / 2, yBoundary / 2);
}

std::vector<Component*> Entity::getComponents() {
  return this->boundComponents;
}

