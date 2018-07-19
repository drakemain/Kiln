#include "../headers/Sprite.h"
#include <iostream>

Sprite::Sprite(Texture* texture) {
  this->texture = texture->getTexture();
  this->dimensions.w = texture->getWidth();
  this->dimensions.h = texture->getHeight();
}

Sprite::Sprite() {}

Coordinate Sprite::getPosition() const {
  return this->position;
}

Dim Sprite::getDimensions() const {
  return this->dimensions;
}

// void Sprite::fromTexture(Texture* texture) {
//   if (texture) {
//     std::cout << "ASSIGN" << std::endl;
//     this->texture = texture;
//     std::cout << "ASSIGNED" << std::endl;
//   } else {
//     std::cerr << "Bad texture!" << std::endl;
//   }
// }

// void Sprite::fromText(std::string text, TTF_Font* font, SDL_Renderer* renderer) {
//   SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{0x88, 0x88, 0x88, 0xFF});
//   this->texture = new Texture();
//   this->texture->create(surface, renderer);

//   SDL_FreeSurface(surface);
// }

void Sprite::setWidth(unsigned int width) {
  this->dimensions.w = width;
}

void Sprite::setHeight(unsigned int height) {
  this->dimensions.h = height;
}

void Sprite::setPosition(int x, int y) {
  this->position.x = x;
  this->position.y = y;
}

void Sprite::render(SDL_Renderer* renderer) const {
  SDL_Rect container;
  container.w = this->dimensions.w;
  container.h = this->dimensions.h;
  container.x = this->position.x;
  container.y = this->position.y;

  SDL_RenderCopy(
    renderer,
    this->texture,
    NULL,
    &container  
  );
}