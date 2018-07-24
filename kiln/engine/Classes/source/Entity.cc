#include "../headers/Entity.h"

Entity::Entity() {}
Entity::~Entity() {}

FCoordinate Entity::getWorldPosition() const {
  return this->worldPosition;
}

void Entity::setWorldPosition(float x, float y) {
  this->worldPosition.x = x;
  this->worldPosition.y = y;
}

void Entity::setWorldPosition(FCoordinate position) {
  this->worldPosition = position;
}

void Entity::centerInWindow(unsigned int xBoundary, unsigned int yBoundary) {
  this->setWorldPosition(xBoundary / 2, yBoundary / 2);
}