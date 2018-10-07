#pragma once
#include "kiln/engine/Modules/ModuleSub.h"
#include "kiln/engine/Modules/KilnModule.h"
#include <iostream>

class InitSub : public ModuleSub {
public:
  InitSub(class KilnModule* mod);
  void init() override;

  void cleanup() override;
  void pause() override;
  void resume() override;
  void handleEvent(SDL_Event* event) override;
  void tick(float deltaTime) override;
  void render(SDL_Renderer* renderer) override;

private:
  float runtime = 0;
};