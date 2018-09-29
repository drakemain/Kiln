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
  float vxSum = 0;
  float vx = 0;
  float vySum = 0;
  float vy = 0;

  Uint32 startTime = 0;
  float runTime = 0.f;
};