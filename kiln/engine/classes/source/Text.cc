#include "../headers/Text.h"
#include <iostream>

Text::Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
  this->text = text;
  this->font = font;
  this->color = color;
  this->draw(renderer);
}

Text::~Text() {
  SDL_DestroyTexture(this->texture);
}

void Text::draw(SDL_Renderer* renderer) {
  this->clear();

  SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);

  if (!surface) {
    // TODO: handle missing texture
    std::cerr << "Failed to render text!\n\t" << TTF_GetError() << std::endl;
  } else {
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->setWidth(surface->w);
    this->setHeight(surface->h);
  }

  this->wasModified = false;
}

void Text::setText(std::string text) {
  this->wasModified = true;

  this->text = text;
}

void Text::setFont(TTF_Font* font) {
  this->wasModified = true;

  this->font = font;
}

void Text::setColor(SDL_Color color) {
  this->wasModified = true;

  this->color = color;
}

bool Text::checkWasModified() const {
  return this->wasModified;
}

void Text::clear() {
  SDL_DestroyTexture(this->texture);
  this->texture = nullptr;
}