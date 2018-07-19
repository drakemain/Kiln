#pragma once

#include "kiln/engine/States/headers/State.h"
#include "kiln/engine/Kiln.h"
#include "kiln/engine/classes/headers/Sprite.h"

class InitState : public State {
public:
  InitState(CoreManagement& coreManagement);

  void init() override;
  void cleanup() override;

  void pause() override;
  void resume() override;

  void handleEvents() override;
  void tick(float deltaTime) override;
  void render() override;

private:
  float uptime;
  CoreManagement& coreManagement;
  Sprite testSprite;
};