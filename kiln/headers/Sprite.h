#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Base.h"

class Sprite : public Base {
public:
  ~Sprite();
  bool load(std::string imgPath);

  int getWidth() const;
  int getHeight() const;
  Coordinate getPosition() const;

  void setWidth(int width);
  void setHeight(int height);
  void setPosition(int x, int y);

  SDL_Texture* getTexture() const;
  SDL_Rect* getContainer();

private:
  SDL_Texture* texture;
  SDL_Rect container;
};