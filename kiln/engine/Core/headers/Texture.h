#pragma once

#include "kiln/engine/Utils/headers/Dim.h"
#include <string>

class Texture {
public:
  Texture();
  ~Texture();

private:
  Texture(const class Texture& texture);
  Texture(const char* path, class SDL_Renderer* renderer);

  bool create(const char* filePath, class SDL_Renderer* renderer);
  bool create(class SDL_Surface* surface, class SDL_Renderer* renderer);

public:
  unsigned int getWidth() const;
  unsigned int getHeight() const;
  class SDL_Texture* getTexture() const;

  Texture* copy();
  void destroy();

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);

  static Texture* newTexture(const char* path, class SDL_Renderer* renderer);

private:
  class SDL_Texture* texture = nullptr;
  Dim dimensions;
};