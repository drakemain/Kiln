#include "../headers/Entity.h"
#include "kiln/engine/Classes/Components/headers/EntityComponent.h"
#include <iostream>

Entity::Entity() {}
Entity::~Entity() {}

FCoordinate Entity::getWorldPosition() const {
  return this->worldPosition;
}

void Entity::setWorldPosition(float x, float y) {
  this->worldPosition.x = x;
  this->worldPosition.y = y;

  this->updateComponentPositions();
}

void Entity::setWorldPosition(FCoordinate position) {
  std::cout << "Modifying entity position" << std::endl;
  std::cout << "\t{" << position.x << ", " << position.y << "}" << std::endl;
  
  this->worldPosition = position;
  this->updateComponentPositions();
}

void Entity::bindComponent(EntityComponent* component) {
  std::cout << "Binding component" << std::endl;
  
  for (EntityComponent* comp : this->boundComponents) {
    if (component == comp) {
      return;
    }
  }

  this->boundComponents.push_back(component);
}

void Entity::updateComponentPositions() {
  for (EntityComponent* comp : this->boundComponents) {
    std::cout << "\tUpdating component." << std::endl;
    comp->updatePosition();
  }
}

void Entity::centerInWindow(unsigned int xBoundary, unsigned int yBoundary) {
  this->setWorldPosition(xBoundary / 2, yBoundary / 2);
}