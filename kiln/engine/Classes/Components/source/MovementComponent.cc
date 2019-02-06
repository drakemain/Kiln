#include "../headers/MovementComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"

MovementComponent::MovementComponent(Entity* owner)
: Component(owner) {}

void MovementComponent::setVelocity(Velocity velocity) {
  this->velocity = velocity;
}

void MovementComponent::setVelocity(float x, float y) {
  this->velocity.x = x;
  this->velocity.y = y;
}

Velocity MovementComponent::getVelocity() const {
  return this->velocity;
}

void MovementComponent::tick(float deltaTime) {
  if (!this->velocity.isZero(.01f)) {
    this->updatePosition(deltaTime);
  }
}

void MovementComponent::updatePosition(float deltaTime) {
  ICoordinate currentPosition = this->getOwner()->getWorldPosition();
  ICoordinate newPosition;

  newPosition.x = (this->velocity.x * (deltaTime/1000.f)) + currentPosition.x;
  newPosition.y = (this->velocity.y * (deltaTime/1000.f)) + currentPosition.y;

  this->getOwner()->setWorldPosition(newPosition);
}