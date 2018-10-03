#pragma once
#include "kiln/engine/Modules/KilnModule.h"
#include "subs/init.h"

class TetrisModule : public KilnModule {
public:
  TetrisModule() {}
  virtual bool init() override;
  virtual void start() override;
  virtual void handleEvent(SDL_Event* event) override;
  virtual void tick(float deltaTime) override;
  virtual void render() override;


};