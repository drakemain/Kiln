#include "../headers/Sprite.h"
#include <iostream>

Sprite::Sprite(Texture* texture)
: SpriteBase(texture) {}

Sprite::Sprite() {}

void Sprite::centerInWindow(unsigned int xBound, unsigned int yBound) {
  FCoordinate windowCenter;
  windowCenter.x = xBound / 2;
  windowCenter.y = yBound / 2;

  this->setWorldPosition(
    windowCenter.x - (this->getDimensions().w / 2),
    windowCenter.y - (this->getDimensions().h / 2)
  );
}

void Sprite::render(SDL_Renderer* renderer) const {
  SDL_Rect container;
  container.w = this->getDimensions().w;
  container.h = this->getDimensions().h;
  container.x = this->getWorldPosition().x;
  container.y = this->getWorldPosition().y;

  SDL_RenderCopyEx(
    renderer,
    this->texture,
    NULL,
    &container,
    this->getRotationDegrees(),
    NULL,
    SDL_FLIP_NONE  
  );
}