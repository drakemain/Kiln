#pragma once
#include "kiln/engine/Modules/ModuleSub.h"
#include "kiln/engine/Kiln.h"
#include <vector>

class Menu : public ModuleSub {
public:
  Menu(class KilnModule* module);
  
  virtual void handleEvent(SDL_Event* event) override;
  virtual void tick(float deltaTime) override;
  virtual void render(SDL_Renderer* renderer);

protected:
  void createButton(class Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  void createButton(class Texture* texture);
  void createButton(class Button* button);

  void createStatic(class Sprite* sprite);
  void createStatic(class Texture* texture);

  // AssetDependencies assetDependencies;
private:
  std::vector<class Sprite*> staticElements;
  std::vector<class Button*> buttons;
  SDL_Color backgroundColor;

  float runTime = 0.f;
};