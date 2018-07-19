#pragma once
#include "Sprite.h"
#include <SDL_ttf.h>

class Text : public Sprite {
public:
  Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  ~Text();


};