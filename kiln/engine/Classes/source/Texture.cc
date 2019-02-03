#include "../headers/Texture.h"
#include <iostream>

Texture::Texture() {}

Texture::Texture(const Texture& other) {
  this->texture = other.getTexture();
  this->dimensions.h = other.getHeight();
  this->dimensions.w = other.getWidth();
}

Texture::~Texture() {
  this->destroy();
}

bool Texture::create(std::string filePath, SDL_Renderer* renderer) {
  bool success = false;

  SDL_Surface* surface = IMG_Load(filePath.c_str());

  if (surface == NULL) {
    std::cerr << "Failed to create Texture:" << "\n\t" << IMG_GetError() << std::endl;
  } else {
    success = this->create(surface, renderer);
    SDL_FreeSurface(surface);
  }

  return success;
}

bool Texture::create(SDL_Surface* surface, SDL_Renderer* renderer) {
  if (!surface || !renderer) { return false; }

  SDL_Texture* temp = SDL_CreateTextureFromSurface(renderer, surface);

  if (temp == NULL) {
    return false;
  }

  this->destroy();
  this->texture = temp;
  this->dimensions.w = surface->w;
  this->dimensions.h = surface->h;

  return true;
}

unsigned int Texture::getWidth() const {
  return this->dimensions.w;
}

unsigned int Texture::getHeight() const {
  return this->dimensions.h;
}

void Texture::setWidth(unsigned int width) {
  this->dimensions.w = width;
}

void Texture::setHeight(unsigned int height) {
  this->dimensions.h = height;
}

SDL_Texture* Texture::getTexture() const {
  if (!this->texture) {
    std::cout << "MISSING TEXTURE! Using placeholder." << std::endl;
    return Texture::placeholder->getTexture();
  }

  return this->texture;
}

Texture* Texture::copy() {
  return new Texture(*this);
}

void Texture::destroy() {
  if (this->texture) {
    SDL_DestroyTexture(this->texture);
  }

  this->texture = nullptr;
}