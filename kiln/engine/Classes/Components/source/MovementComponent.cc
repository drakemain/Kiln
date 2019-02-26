#include "../headers/MovementComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"

#include <stdio.h>

MovementComponent::MovementComponent() {}

MovementComponent::MovementComponent(Entity* owner)
: Component(owner) {}

void MovementComponent::consumeDirection(Vec direction) {
  this->accumulatedDirection = this->accumulatedDirection + direction;
}

Vec MovementComponent::getVelocity() const {
  return this->velocity;
}

void MovementComponent::tick(float deltaTime) {
  Vec updatedVelocity;
  
  if (!this->accumulatedDirection.isZero(.01f)) {
    updatedVelocity = KMath::Vector::interpToConst(this->velocity, this->accumulatedDirection.normalize() * this->maxVelocity, deltaTime, this->maxAcceleration);
  } else {
    updatedVelocity = KMath::Vector::interpToConst(this->velocity, {0.f, 0.f}, deltaTime, this->maxAcceleration);
  }

  this->velocity = updatedVelocity;
  this->accumulatedDirection = {0.f, 0.f};

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