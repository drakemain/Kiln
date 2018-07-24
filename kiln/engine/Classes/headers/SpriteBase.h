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
  void setRotation(float degrees);

private:
  Dim dimensions;
  float rotationDegrees = 0.f;

protected:
  SDL_Texture* texture;
};