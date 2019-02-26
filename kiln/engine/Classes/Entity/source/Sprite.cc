#include "../headers/Sprite.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"

Sprite::Sprite() {
  this->sprite = new SpriteComponent(this);
}

Sprite::Sprite(Texture* texture) {
  this->sprite = new SpriteComponent(this, texture);
}

SpriteComponent* Sprite::getComponent() {
  return this->sprite;
}

Dim Sprite::getDimesions() const {
  return this->sprite->getDimensions();
}