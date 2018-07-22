#pragma once
#include "kiln/engine/States/headers/State.h"
#include "kiln/engine/Classes/headers/Sprite.h"
#include "Button.h"
#include "kiln/engine/Kiln.h"
#include <vector>

class Menu : public State {
public:
  Menu(CoreManagement& core);

  virtual void init();
  virtual void cleanup();

  virtual void pause();
  virtual void resume();
  
  virtual void handleEvent(SDL_Event* event);
  virtual void tick(float deltaTime);
  virtual void render();

private:
  std::vector<Sprite*> staticElements;
  std::vector<Button*> buttons;
  CoreManagement& core;
  SDL_Color backgroundColor;

  float runTime = 0.f;
};