#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Base.h"
#include "Texture.h"

class Sprite : public Base {
public:
  void fromTexture(Texture* texture);
  bool fromText(const std::string text, const std::string fontName);

  void setWidth(int width);
  void setHeight(int height);
  void setPosition(int x, int y);

  void render() const;

private:
  Coordinate position;
  Texture* texture;
};