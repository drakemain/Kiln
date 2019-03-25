#include "../headers/SpriteComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include "kiln/engine/Core/headers/Texture.h"
#include "lib/kilnlog/include/KilnLog.h"
#include <SDL.h>

SpriteComponent::SpriteComponent() {}

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

void SpriteComponent::setShouldRender(const bool shouldRender) {
  this->shouldRender = shouldRender;
}

bool SpriteComponent::checkShouldRender() const {
  return this->shouldRender;
}

void SpriteComponent::setWidth(unsigned int width) {
  this->originalDim.w = width;
  this->renderDim.w = width * this->scale;
}

void SpriteComponent::setHeight(unsigned int height) {
  this->originalDim.h = height;
  this->renderDim.h = height * this->scale;
}

void SpriteComponent::setScale(float scale) {
  this->scale = scale;
  this->renderDim.w = this->originalDim.w * scale;
  this->renderDim.h = this->originalDim.h * scale;
}

void SpriteComponent::setTexture(Texture* texture) {
  if (!texture) {
    KLog.put(KLOG_WAR, "Sprite component tried to set null texture.");
    return;
  }

  this->setTexture(texture->getTexture());
  this->originalDim = {texture->getWidth(), texture->getHeight()};
  this->renderDim = originalDim;
}

void SpriteComponent::setTexture(SDL_Texture* texture) {
  this->clear();
  this->texture = texture;
}

FCoordinate SpriteComponent::getWorldPosition() const {
  return this->getOwner()->getWorldPosition() + this->getRelativePosition();
}

Dim SpriteComponent::getDimensions() const {
  return this->renderDim;
}

float SpriteComponent::getScale() const {
  return this->scale;
}

float SpriteComponent::getRotationDegrees() const {
  return this->rotationDegrees;
}

SDL_Texture* SpriteComponent::getTexture() {
  return this->texture;
}

void SpriteComponent::render(SDL_Renderer* renderer) {
  if (!this->shouldRender) { return; }

  SDL_Texture* texture = this->getTexture();
  
  if (!texture) {
    KLog.put(KLOG_WAR, "Cannot render SpriteComponent: null texture.");
    this->shouldRender = false;
    return;
  }

  SDL_Rect container;
  container.w = this->getDimensions().w;
  container.h = this->getDimensions().h;
  container.x = getWorldPosition().x;
  container.y = getWorldPosition().y;

  SDL_RenderCopyEx(
          renderer,
          texture,
          NULL,
          &container,
          this->getRotationDegrees(),
          NULL,
          SDL_FLIP_NONE
  );
}

void SpriteComponent::clear() {
  SDL_DestroyTexture(this->texture);
  this->texture = nullptr;
  this->originalDim = {0, 0};
  this->renderDim = {0, 0};
}
