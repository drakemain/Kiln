#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"

struct Coordinate {
  int x = 0;
  int y = 0;
};

struct Dim {
  unsigned int w = 0;
  unsigned int h = 0;
};

class Sprite {
public:
  Sprite(Texture* texture);
  Sprite();

  Coordinate getPosition() const;
  Dim getDimensions() const;

  // void fromTexture(Texture* texture);
  // void fromText(std::string text, TTF_Font* font, SDL_Renderer* renderer);

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);
  void setPosition(int x, int y);

  void render(SDL_Renderer* renderer) const;

private:
  Coordinate position;
  Dim dimensions;

protected:
  SDL_Texture* texture;
};