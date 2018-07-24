#include "../headers/MovementComponent.h"
#include <iostream>

MovementComponent::MovementComponent(Entity* owner)
: Component(owner) {}

void MovementComponent::setVelocity(Velocity velocity) {
  this->velocity = velocity;
}

void MovementComponent::setVelocity(float x, float y) {
  this->velocity.x = x;
  this->velocity.y = y;
}

void MovementComponent::tick(float deltaTime) {
  if (!this->velocity.isZero(.01f)) {
    this->updatePosition(deltaTime);
  }
}

void MovementComponent::updatePosition(float deltaTime) {
  FCoordinate currentPosition = this->getOwner()->getWorldPosition();
  FCoordinate newPositition;

  newPositition.x = (this->velocity.x * (deltaTime/1000.f)) + currentPosition.x;
  newPositition.y = (this->velocity.y * (deltaTime/1000.f)) + currentPosition.y;

  this->getOwner()->setWorldPosition(newPositition);
}