#pragma once

#include "kiln/engine/Classes/Base/headers/TextBase.h"
#include "Component.h"
// #include <SDL_ttf.h>
// #include "SpriteComponent.h"

class TextComponent : public TextBase, public Component {
public:
    TextComponent(Entity* owner, std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color);
    virtual ~TextComponent();

    void start() override;
    void tick(float deltaTime) override;

    void render(SDL_Renderer* renderer);
};