#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Classes/headers/Entity.h"

TextComponent::TextComponent(Entity* owner, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
: EntityComponent(owner), TextBase(text, font, color, renderer) {}

void TextComponent::render(SDL_Renderer* renderer) {
  SDL_Rect container;
  container.w = this->getDimensions().w;
  container.h = this->getDimensions().h;
  container.x = this->getWorldPosition().x;
  container.y = this->getWorldPosition().y;

  SDL_RenderCopyEx(
    renderer,
    this->getTexture(),
    NULL,
    &container,
    this->getRotationDegrees(),
    NULL,
    SDL_FLIP_NONE  
  );
}