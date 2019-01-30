#include <kiln/engine/Definitions/Colors.h>
#include <iostream>
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Classes/headers/Entity.h"

TextComponent::TextComponent(Entity* owner, std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color = KILN_COLOR::DARK_GREY)
: TextBase(text, font, color, renderer), Component(owner) {}

TextComponent::~TextComponent() {}

void TextComponent::start() {}

void TextComponent::tick(float deltaTime) {}

void TextComponent::render(SDL_Renderer* renderer) {
  SpriteBase::render(renderer, this->getWorldPosition());
}