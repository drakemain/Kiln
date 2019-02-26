#pragma once

#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include <SDL_ttf.h>
#include <string>

class TextComponent : public SpriteComponent {
public:
  TextComponent(std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color);
  TextComponent(Entity* owner, std::string text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color);
  virtual ~TextComponent();

  void start() override;
  void tick(float deltaTime) override;

public:
  void setText(std::string text);
  void setFont(TTF_Font* font);
  void setColor(SDL_Color color);

  bool checkWasModified() const;

  void render(SDL_Renderer*) override;
private:
  void draw(SDL_Renderer* renderer);
  
  std::string text;
  TTF_Font* font;
  SDL_Color color;
  SDL_Renderer* renderer;
  
  bool wasModified = false;
};