#include "../headers/SpriteComponent.h"

SpriteComponent::SpriteComponent(Entity* owner, Texture* texture)
: Component(owner), SpriteBase(texture) {}


SpriteComponent::SpriteComponent(Entity* onwer)
: Component(onwer) {}


void SpriteComponent::start() {}

void SpriteComponent::tick(float deltaTime) {}

void SpriteComponent::setRelativePosition(int x, int y) {
  this->relativePosition.x = x;
  this->relativePosition.y = y;
}

void SpriteComponent::setRelativePosition(ICoordinate position) {
  this->relativePosition = position;
}

ICoordinate SpriteComponent::getRelativePosition() const {
  return this->relativePosition;
}

ICoordinate SpriteComponent::getWorldPosition() const {
  return this->getOwner()->getWorldPosition() + this->relativePosition;
}

void SpriteComponent::render(SDL_Renderer* renderer) {
  SpriteBase::render(renderer, this->getWorldPosition());
}
