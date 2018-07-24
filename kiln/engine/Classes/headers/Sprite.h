#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"
#include "Entity.h"
#include "kiln/engine/Utils/headers/Dim.h"

class Sprite : public Entity {
public:
  Sprite(Texture* texture);
  Sprite();

  Dim getDimensions() const;
  float getRotationDegrees() const;

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);
  void setRotation(float degrees);

  void render(SDL_Renderer* renderer) const;

  void centerInWindow(unsigned int xBound, unsigned int yBound) override;

private:
  Dim dimensions;
  float rotationDegrees = 0.f;

protected:
  SDL_Texture* texture = nullptr;
};