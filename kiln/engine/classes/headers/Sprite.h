#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Texture.h"

struct Coordinate {
  int x;
  int y;
};

class Sprite {
public:
  void fromTexture(Texture* texture);
  bool fromText(const std::string text, const std::string fontName);

  void setWidth(int width);
  void setHeight(int height);
  void setPosition(int x, int y);

  void render(SDL_Renderer* renderer) const;

private:
  Coordinate position;
  Texture* texture;
};