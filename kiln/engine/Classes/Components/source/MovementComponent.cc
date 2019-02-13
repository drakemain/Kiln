#include "../headers/MovementComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"

#include <stdio.h>

MovementComponent::MovementComponent(Entity* owner)
: Component(owner) {}

void MovementComponent::consumeDirection(Vec direction) {
  this->accumulation = this->accumulation + direction;
}

Vec MovementComponent::getVelocity() const {
  return this->velocity;
}

void MovementComponent::tick(float deltaTime) {
  if (!this->accumulation.isZero(.01f)) {
    this->accumulation = this->accumulation.normalize();
    this->velocity = this->accumulation * this->maxVelocity;

    this->updatePosition(deltaTime);
    
    this->accumulation = Vec(0.f, 0.f);
    this->velocity = Vec(0.f, 0.f);
  }
}

void MovementComponent::updatePosition(float deltaTime) {
  FCoordinate currentPosition = this->getOwner()->getWorldPosition();
  FCoordinate newPosition;

  newPosition.x = (this->velocity.x * deltaTime / 1000) + currentPosition.x;
  newPosition.y = (this->velocity.y * deltaTime / 1000) + currentPosition.y;

  this->getOwner()->setWorldPosition(newPosition);
}