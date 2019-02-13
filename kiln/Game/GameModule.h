#pragma once
#include "kiln/engine/Module/KilnModule.h"

class GameModule : public KilnModule {
public:
  GameModule() {}
  virtual bool init() override;
  virtual void start() override;
  virtual void handleEvent(const SDL_Event* event) override;
  virtual void tick(float deltaTime) override;
  virtual void render() override;
};