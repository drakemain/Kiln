#include "../headers/Component.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"

Component::Component(Entity* owner) {
  owner->bindComponent(this);
  this->updatePosition();
}

Component::Component() {}

Component::~Component() {}

void Component::setRelativePosition(FCoordinate pos) {
  this->relativePosition = pos;
  this->updatePosition();
}

void Component::setRelativePosition(int x, int y) {
  this->setRelativePosition(FCoordinate::fromInt({x, y}));
}

// void Component::setRelativePosition(Position position) {

// }

FCoordinate Component::getRelativePosition() const {
  return this->relativePosition;
}

FCoordinate Component::getWorldPosition() const {
  return this->worldPosition;
}

void Component::updatePosition() {
  this->setWorldPosition();
}

void Component::setWorldPosition() {
  FCoordinate ownerPosition = this->getOwner()->getWorldPosition();
  FCoordinate myWorldPosition;

  myWorldPosition.x = ownerPosition.x + this->relativePosition.x;
  myWorldPosition.y = ownerPosition.y + this->relativePosition.y;

  this->worldPosition = myWorldPosition;
}

Entity* Component::getOwner() const {
  return this->owner;
}
