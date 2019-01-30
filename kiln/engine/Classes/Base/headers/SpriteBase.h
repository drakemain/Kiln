#pragma once
#include "kiln/engine/Utils/headers/Dim.h"

class SpriteBase {
public:
  SpriteBase(class Texture* texture);
  SpriteBase();

  virtual ~SpriteBase();

  Dim getDimensions() const;
  float getRotationDegrees() const;

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);
  void setScale(float scale);
  void setRotation(float degrees);

  void setTexture(class SDL_Texture* texture);
  class SDL_Texture* getTexture();

  void clear();

protected:
  void render(class SDL_Renderer* renderer, class ICoordinate position);

private:
  Dim dimensions;
  Dim originalDim;
  float rotationDegrees = 0.f;
  SDL_Texture* texture = nullptr;
};