#include "../headers/Component.h"

Component::Component(Entity* owner)
: owner(owner) {

}

Component::Component() {}

Component::~Component() {}

void Component::setRelativePosition(ICoordinate pos) {
  this->relativePosition = pos;
}

void Component::setRelativePosition(int x, int y) {
  this->setRelativePosition({x, y});
}

ICoordinate Component::getRelativePosition() const {
  return this->relativePosition;
}

ICoordinate Component::getWorldPosition() const {
  return this->worldPosition;
}

void Component::updatePosition() {
  this->setWorldPosition();
}

void Component::setWorldPosition() {
  ICoordinate ownerPosition = this->getOwner()->getWorldPosition();
  ICoordinate myWorldPosition;

  myWorldPosition.x = ownerPosition.x + this->relativePosition.x;
  myWorldPosition.y = ownerPosition.y + this->relativePosition.y;

  this->worldPosition = myWorldPosition;
}

Entity* Component::getOwner() const {
  return this->owner;
}
