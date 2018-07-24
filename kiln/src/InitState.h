#pragma once

#include "kiln/engine/States/headers/State.h"
#include "kiln/engine/Kiln.h"
#include "kiln/engine/Classes/headers/Sprite.h"
#include "MovementTest.h"
#include "kiln/engine/Classes/headers/Text.h"

class InitState : public State {
public:
  InitState(CoreManagement& coreManagement);
  ~InitState();

  void init() override;
  void cleanup() override;

  void pause() override;
  void resume() override;

  void handleEvent(SDL_Event* event) override;
  void tick(float deltaTime) override;
  void render() override;

private:
  CoreManagement& coreManagement;
  Sprite* testSprite;
  MovableSprite* movableSprite;
  Text* testText;
  Mix_Chunk* sound;

  int vSamples = 0;
  float vSum = 0;
  float v = 0;

  Uint32 startTime;
  float runTime = 0.f;
};