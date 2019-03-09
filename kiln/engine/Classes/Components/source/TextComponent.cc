#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include "kiln/engine/Definitions/Colors.h"
#include "lib/kilnlog/include/KilnLog.h"
#include <SDL_ttf.h>
#include <SDL.h>

TextComponent::TextComponent(std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color)
: text(text), font(font), color(color), renderer(renderer) {
  this->draw(renderer);
}

TextComponent::TextComponent(Entity* owner, std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color = KILN_COLOR::DARK_GREY)
: SpriteComponent(owner), text(text), font(font), color(color), renderer(renderer) {
  this->draw(renderer);
}

TextComponent::~TextComponent() {
  SDL_DestroyTexture(this->getTexture());
}

void TextComponent::start() {
  
}

void TextComponent::tick(float deltaTime) {
  if (this->wasModified) {
    this->draw(this->renderer);
  }
}

void TextComponent::draw(SDL_Renderer* renderer) {
  if (this->text.size() == 0) { return; }

  if (!this->font) {
    this->clear();
    return;
  }

  SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
  if (!surface) {
    // TODO: handle missing Texture
    KLog.put(KLOG_WAR, "Failed to render text surface! %s", TTF_GetError());
  } else {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture) {
      this->setTexture(texture);
      this->setWidth(surface->w);
      this->setHeight(surface->h);
    } else {
      KLog.put(KLOG_WAR, "Failed to render texture from surface! %s", SDL_GetError());
    }

    SDL_FreeSurface(surface);
  }

  this->wasModified = false;
}

void TextComponent::setText(std::string text) {
  this->text = text;
  this->wasModified = true;
}

void TextComponent::setFont(TTF_Font* font) {
  this->font = font;
  this->wasModified = true;
}

void TextComponent::setColor(SDL_Color color) {
  this->color = color;
  this->wasModified = true;
}

void TextComponent::render(SDL_Renderer* renderer) {
  SpriteComponent::render(renderer);
}