#include "../headers/SpriteComponent.h"
#include "../../headers/Entity.h"
#include "kiln/engine/Classes/headers/Texture.h"

SpriteComponent::SpriteComponent(Entity* owner, Texture* texture)
: Component(owner) {
  this->setTexture(texture);
}

SpriteComponent::SpriteComponent(Entity* owner)
: Component(owner) {}

SpriteComponent::SpriteComponent(Texture* texture) {
  this->setTexture(texture);
}

void SpriteComponent::start() {}

void SpriteComponent::tick(float deltaTime) {}

void SpriteComponent::setWidth(unsigned int width) {
  this->originalDim.w = width;
  this->renderDim.w = width;
}

void SpriteComponent::setHeight(unsigned int height) {
  this->originalDim.h = height;
  this->renderDim.h = height;
}

void SpriteComponent::setScale(float scale) {
  this->renderDim.w = this->originalDim.w * scale;
  this->renderDim.h = this->originalDim.h * scale;
}

void SpriteComponent::setTexture(Texture* texture) {
  this->setTexture(texture->getTexture());
  this->originalDim = {texture->getWidth(), texture->getHeight()};
  this->renderDim = originalDim;
}

void SpriteComponent::setTexture(SDL_Texture* texture) {
  this->clear();
  this->texture = texture;
}

ICoordinate SpriteComponent::getWorldPosition() const {
  return this->getOwner()->getWorldPosition() + this->getRelativePosition();
}

Dim SpriteComponent::getDimensions() const {
  return this->renderDim;
}

float SpriteComponent::getRotationDegrees() const {
  return this->rotationDegrees;
}

SDL_Texture* SpriteComponent::getTexture() {
  return this->texture;
}

void SpriteComponent::render(SDL_Renderer* renderer) {
  SDL_Rect container;
  container.w = this->getDimensions().w;
  container.h = this->getDimensions().h;
  container.x = getWorldPosition().x;
  container.y = getWorldPosition().y;

  SDL_RenderCopyEx(
          renderer,
          this->getTexture(),
          NULL,
          &container,
          this->getRotationDegrees(),
          NULL,
          SDL_FLIP_NONE
  );
}

void SpriteComponent::clear() {
  this->texture = nullptr;
  this->originalDim = {0, 0};
  this->renderDim = {0, 0};
}