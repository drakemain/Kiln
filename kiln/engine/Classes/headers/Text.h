#pragma once
#include "Sprite.h"
#include <SDL_ttf.h>
#include <string>

class Text : public Sprite {
public:
  Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  ~Text();

  void draw(SDL_Renderer* renderer);
  void setText(std::string text);
  void setFont(TTF_Font* font);
  void setColor(SDL_Color color);

  bool checkWasModified() const;

private:
  std::string text;
  TTF_Font* font;
  SDL_Color color;
  
  bool wasModified = false;
};