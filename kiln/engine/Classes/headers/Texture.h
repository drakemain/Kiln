#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "kiln/engine/Utils/headers/Dim.h"

class Texture {
public:
  Texture();
  Texture(const Texture& texture);
  ~Texture();
  bool create(std::string filePath, SDL_Renderer* renderer);
  bool create(SDL_Surface* surface, SDL_Renderer* renderer);

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  SDL_Texture* getTexture() const;

  Texture* copy();
  void destroy();

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);

  static Texture* placeholder;

private:
  SDL_Texture* texture;
  Dim dimensions;
};