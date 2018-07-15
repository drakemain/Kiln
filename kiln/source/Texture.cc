#include "kiln/headers/Texture.h"
#include <iostream>

Texture::~Texture() {
  SDL_DestroyTexture(this->texture);
}

bool Texture::create(std::string filePath) {
  SDL_Surface* surface = IMG_Load(filePath.c_str());

  if (surface == NULL) {
    std::cerr << "Failed to create Texture:" << "\n\t" << IMG_GetError() << std::endl;
    return false;
  }

  this->texture = SDL_CreateTextureFromSurface(this->getBaseRenderer(), surface);

  if (this->texture == NULL) {
    std::cerr << "Failed to convert img to texture\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  this->width = surface->w;
  this->height = surface->h;

  SDL_FreeSurface(surface);

  return true;
}

int Texture::getWidth() const {
  return this->width;
}

int Texture::getHeight() const {
  return this->height;
}

void Texture::setWidth(int width) {
  if (width >= 0) {
    this->width = width;
  }
}

void Texture::setHeight(int height) {
  if (height >= 0) {
    this->height = 0;
  }
}

SDL_Texture* Texture::getTexture() const {
  return this->texture;
}