#include "../headers/MovementComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"

MovementComponent::MovementComponent(Entity* owner)
: Component(owner) {}

void MovementComponent::setVelocity(Vec velocity) {
  this->velocity = velocity;
}

void MovementComponent::setVelocity(float x, float y) {
  this->velocity.x = x;
  this->velocity.y = y;
}

void MovementComponent::accelerate(const Vec& vector) {
  this->velocity.x += vector.x;
  this->velocity.y += vector.y;
}

Vec MovementComponent::getVelocity() const {
  return this->velocity;
}

float MovementComponent::getSpeed() {
  return this->velocity.magnitude();
}

void MovementComponent::tick(float deltaTime) {
  if (!this->velocity.isZero(.01f)) {
    this->updatePosition(deltaTime);
  }
}

void MovementComponent::updatePosition(float deltaTime) {
  FCoordinate currentPosition = this->getOwner()->getWorldPosition();
  FCoordinate newPosition;

  newPosition.x = (this->velocity.x * deltaTime / 1000) + currentPosition.x;
  newPosition.y = (this->velocity.y * deltaTime / 1000) + currentPosition.y;

  this->getOwner()->setWorldPosition(newPosition);
}