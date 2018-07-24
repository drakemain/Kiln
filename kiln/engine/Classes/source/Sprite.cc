#include "../headers/Sprite.h"
#include <iostream>

Sprite::Sprite(Texture* texture) {
  this->texture = texture->getTexture();
  this->dimensions.w = texture->getWidth();
  this->dimensions.h = texture->getHeight();
}

Sprite::Sprite() {}

Dim Sprite::getDimensions() const {
  return this->dimensions;
}

float Sprite::getRotationDegrees() const {
  return this->rotationDegrees;
}

void Sprite::setWidth(unsigned int width) {
  this->dimensions.w = width;
}

void Sprite::setHeight(unsigned int height) {
  this->dimensions.h = height;
}

void Sprite::setRotation(float degrees) {
  this->rotationDegrees = degrees;
}

void Sprite::render(SDL_Renderer* renderer) const {
  SDL_Rect container;
  container.w = this->dimensions.w;
  container.h = this->dimensions.h;
  container.x = this->getWorldPosition().x;
  container.y = this->getWorldPosition().y;

  SDL_RenderCopyEx(
    renderer,
    this->texture,
    NULL,
    &container,
    this->rotationDegrees,
    NULL,
    SDL_FLIP_NONE  
  );
}

void Sprite::centerInWindow(unsigned int xBound, unsigned int yBound) {
  FCoordinate windowCenter;
  windowCenter.x = xBound / 2;
  windowCenter.y = yBound / 2;

  this->setWorldPosition(
    windowCenter.x - (this->dimensions.w / 2),
    windowCenter.y - (this->dimensions.h / 2)
  );
}