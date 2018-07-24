#include "../headers/SpriteBase.h"
#include <iostream>

SpriteBase::SpriteBase(Texture* texture) {
  this->texture = texture->getTexture();
  this->dimensions.w = texture->getWidth();
  this->dimensions.h = texture->getHeight();
}

SpriteBase::SpriteBase() {}

SpriteBase::~SpriteBase() {}

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