#pragma once

#include "kiln/engine/Utils/headers/Dim.h"
#include <string>

class Texture {
public:
  Texture();
  Texture(const class Texture& texture);
  ~Texture();
  bool create(std::string filePath, class SDL_Renderer* renderer);
  bool create(class SDL_Surface* surface, class SDL_Renderer* renderer);

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  class SDL_Texture* getTexture() const;

  Texture* copy();
  void destroy();

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);

  static Texture* placeholder;

private:
  class SDL_Texture* texture = nullptr;
  Dim dimensions;
};