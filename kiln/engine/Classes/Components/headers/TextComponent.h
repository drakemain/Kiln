#pragma once
#include "kiln/engine/Classes/headers/TextBase.h"
#include "kiln/engine/Classes/Components/headers/EntityComponent.h"

class TextComponent : public EntityComponent, public TextBase {
public:
  TextComponent(Entity* owner, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);

  void render(SDL_Renderer* renderer);
};