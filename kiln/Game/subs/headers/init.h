#pragma once
#include "kiln/engine/Module/SubModule.h"
#include "kiln/engine/Module/KilnModule.h"
#include <iostream>

class InitSub : public SubModule {
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
  float runtime = 0.f;
};