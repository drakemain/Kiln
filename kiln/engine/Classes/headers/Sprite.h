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
  // ~Sprite();

  Dim getDimensions() const;

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);

  void render(SDL_Renderer* renderer) const;

  void centerInWindow(unsigned int xBound, unsigned int yBound) override;

private:
  Dim dimensions;

protected:
  SDL_Texture* texture = nullptr;
};