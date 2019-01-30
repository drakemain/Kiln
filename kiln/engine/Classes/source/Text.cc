#include "../headers/Text.h"
#include <iostream>

Text::Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
: TextBase(text, font, color, renderer) {}

Text::~Text() {}

void Text::render(SDL_Renderer* renderer) {
  SpriteBase::render(renderer, this->getWorldPosition());
}