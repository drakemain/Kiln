#include "../headers/Entity.h"

Entity::~Entity() {}

Coordinate Entity::getWorldPosition() const {
  return this->worldPosition;
}

void Entity::setWorldPosition(int x, int y) {
  this->worldPosition.x = x;
  this->worldPosition.y = y;
}