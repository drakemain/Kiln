#include "kiln/engine/Classes/headers/TextBase.h"
#include <iostream>

TextBase::TextBase(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
  this->text = text;
  this->font = font;
  this->color = color;
  this->draw(renderer);
}

TextBase::~TextBase() {
  SDL_DestroyTexture(this->getTexture());
}

void TextBase::draw(SDL_Renderer* renderer) {
  this->clear();
  SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
  if (!surface) {
    // TODO: handle missing Texture
    std::cerr << "Failed to render TextBase!\n\t" << TTF_GetError() << std::endl;
  } else {
    this->setTexture(SDL_CreateTextureFromSurface(renderer, surface));
    this->setWidth(surface->w);
    this->setHeight(surface->h);
  }

  this->wasModified = false;
}

void TextBase::setText(std::string text) {
  this->wasModified = true;

  this->text = text;
}

void TextBase::setFont(TTF_Font* font) {
  this->wasModified = true;

  this->font = font;
}

void TextBase::setColor(SDL_Color color) {
  this->wasModified = true;

  this->color = color;
}

bool TextBase::checkWasModified() const {
  return this->wasModified;
}
