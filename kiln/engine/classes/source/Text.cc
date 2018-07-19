#include "../headers/Text.h"
#include <iostream>

Text::Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

  if (!surface) {
    // TODO: handle missing texture
    std::cerr << "Failed to render text!\n\t" << TTF_GetError() << std::endl;
  } else {
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->setWidth(surface->w);
    this->setHeight(surface->h);
  }
}

Text::~Text() {
  SDL_DestroyTexture(this->texture);
}