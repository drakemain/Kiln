#pragma once
#include <SDL.h>
#include "Texture.h"
#include "kiln/engine/Utils/headers/Dim.h"

class SpriteBase {
public:
  SpriteBase(Texture* texture);
  SpriteBase();

  ~SpriteBase();

  Dim getDimensions() const;
  float getRotationDegrees() const;

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);
  void setScale(float scale);
  void setRotation(float degrees);

  virtual void render(SDL_Renderer* renderer) = 0;

  void setTexture(SDL_Texture* texture);
  SDL_Texture* getTexture();

  void clear();

private:
  Dim dimensions;
  Dim originalDim;
  float rotationDegrees = 0.f;
  SDL_Texture* texture = nullptr;
};