#pragma once

#include "kiln/engine/States/headers/State.h"
#include "kiln/engine/Kiln.h"
#include "kiln/engine/classes/headers/Sprite.h"
#include "kiln/engine/classes/headers/Text.h"

class InitState : public State {
public:
  InitState(CoreManagement& coreManagement);
  ~InitState();

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
  Sprite* testSprite;
};