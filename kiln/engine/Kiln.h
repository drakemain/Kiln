#pragma once
#include <SDL.h>
#include "Classes/headers/Sprite.h"
#include "Core/headers/WindowManager.h"
#include "Core/headers/InputManager.h"
#include "Core/headers/AssetManager.h"
#include "States/headers/StateMachine.h"
#include "kiln/engine/Classes/headers/Text.h"
#include "Core/headers/Stats.h"

struct CoreManagement {
  StateMachine state;
  WindowManager windowManager;
  InputManager inputManager;
  AssetManager assetManager;
};

class Kiln {
public:
  Kiln();

  bool init();
  void run();
  void cleanup();

private:
  /* Helper Functions */
  void checkQuit(SDL_Event* event);
  void tick(float deltaTime);
  void render();

  CoreManagement coreManagement;
  
  bool isRunning = true;

  Stats* stats;
};