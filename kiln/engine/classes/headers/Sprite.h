#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"

struct Coordinate {
  int x;
  int y;
};

class Sprite {
public:
  ~Sprite();

  void fromTexture(Texture* texture);
  void fromText(std::string text, TTF_Font* font, SDL_Renderer* renderer);

  void setWidth(int width);
  void setHeight(int height);
  void setPosition(int x, int y);

  void render(SDL_Renderer* renderer) const;

private:
  Coordinate position;
  Texture* texture;
};