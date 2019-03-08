#include "../headers/Texture.h"
#include "lib/kilnlog/include/KilnLog.h"
#include <SDL_image.h>

Texture::Texture() {
  KLog.put(KLOG_DEB, "Created an empty texture.");
}

Texture::Texture(const Texture& other) {
  this->texture = other.getTexture();
  this->dimensions.h = other.getHeight();
  this->dimensions.w = other.getWidth();
}

Texture::~Texture() {
  this->destroy();
}

bool Texture::create(std::string filePath, SDL_Renderer* renderer) {
  KLog.put(KLOG_DEB, "Overwriting existing texture.");
  bool success = false;

  SDL_Surface* surface = IMG_Load(filePath.c_str());

  if (surface == NULL) {
    KLog.put(KLOG_ERR, "Failed to create texture! \n\t%s", IMG_GetError());
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
    KLog.put(KLOG_ERR, "Texture is missing! Using placeholder instead.");
    return Texture::placeholder->getTexture();
  }

  return this->texture;
}

Texture* Texture::copy() {
  return new Texture(*this);
}

void Texture::destroy() {
  if (this->texture) {
    KLog.put(KLOG_DEB, "Destroying existing texture.");
    SDL_DestroyTexture(this->texture);
  }

  this->texture = nullptr;
}