#include "kiln/headers/Sprite.h"
#include <iostream>

Sprite::~Sprite() {
  SDL_DestroyTexture(this->texture);
}

bool Sprite::load(std::string imgPath) {
  SDL_Surface* surface = IMG_Load(imgPath.c_str());

  if (surface == NULL) {
    std::cerr << "Failed to load " << imgPath << "\n\t" << IMG_GetError() << std::endl;
    return false;
  }

  this->texture = SDL_CreateTextureFromSurface(this->getBaseRenderer(), surface);

  if (this->texture == NULL) {
    std::cerr << "Failed to convert img to texture\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  container.w = surface->w;
  container.h = surface->h;
  container.x = 0;
  container.y = 0;

  SDL_FreeSurface(surface);

  return true;
}

int Sprite::getWidth() const {
  return this->container.w;
}

int Sprite::getHeight() const {
  return this->container.h;
}

Coordinate Sprite::getPosition() const {
  Coordinate position;
  position.x = this->container.x;
  position.y = this->container.y;

  return position;
}

void Sprite::setWidth(int width) {
  if (width >= 0) {
    this->container.w = width;
  }
}

void Sprite::setHeight(int height) {
  if (height >= 0) {
    this->container.h = height;
  }
}

void Sprite::setPosition(int x, int y) {
  this->container.x = x;
  this->container.y = y;
}

SDL_Texture* Sprite::getTexture() const {
  return this->texture;
}

SDL_Rect* Sprite::getContainer() {
  return &this->container;
}