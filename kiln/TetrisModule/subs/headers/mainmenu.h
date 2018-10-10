#pragma once
#include "kiln/engine/Classes/Menu/headers/Menu.h"

class MainMenu : public Menu {
public:
  MainMenu(class KilnModule* module);

  virtual void init() override;
  virtual void cleanup() override;

  virtual void pause() override;
  virtual void resume() override;
  
  void handleEvent(SDL_Event* event) override;
  void tick(float deltaTime) override;
  void render(SDL_Renderer* renderer) override;
};