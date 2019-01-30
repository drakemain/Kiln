#include "kiln/engine/Classes/Base/headers/SpriteBase.h"
#include <SDL.h>
#include "kiln/engine/Classes/headers/Texture.h"
#include "../../../Utils/headers/Coordinate.h"
#include <iostream>
// #include "kiln/engine/Classes/Components/headers/SpriteComponent.h"

SpriteBase::SpriteBase(Texture* texture) {
  this->texture = texture->getTexture();
  this->dimensions.w = texture->getWidth();
  this->dimensions.h = texture->getHeight();
  this->originalDim = dimensions;
}

SpriteBase::SpriteBase() {}

SpriteBase::~SpriteBase() {
  if (this->texture) {
    SDL_DestroyTexture(this->texture);
  }
}

Dim SpriteBase::getDimensions() const {
  return this->dimensions;
}

float SpriteBase::getRotationDegrees() const {
  return this->rotationDegrees;
}

void SpriteBase::setWidth(unsigned int width) {
  this->dimensions.w = width;
}

void SpriteBase::setHeight(unsigned int height) {
  this->dimensions.h = height;
}

void SpriteBase::setScale(float scale) {
  this->dimensions.h = this->originalDim.h * scale;
  this->dimensions.w = this->originalDim.w * scale;
}

void SpriteBase::setRotation(float degrees) {
  // keep the new rotation between [0, 360).
  
  if (degrees >= 360.f) {
    degrees = degrees - 360.f;
    this->setRotation(degrees);
  } else if (degrees < 0.f) {
    degrees = 360.f + degrees;
    this->setRotation(degrees);
  } else {
    this->rotationDegrees = degrees;
  }
}

void SpriteBase::render(SDL_Renderer* renderer, ICoordinate position) {
  SDL_Rect container;
  container.w = this->getDimensions().w;
  container.h = this->getDimensions().h;
  container.x = position.x;
  container.y = position.y;

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

void SpriteBase::setTexture(SDL_Texture* texture) {
  this->texture = texture;
}

SDL_Texture* SpriteBase::getTexture() {
  return this->texture;
}

void SpriteBase::clear() {
  if (this->texture) {
    SDL_DestroyTexture(this->texture);
  }

  this->texture = nullptr;
}