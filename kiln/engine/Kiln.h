#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "classes/headers/Sprite.h"
#include "classes/headers/WindowManager.h"
#include "classes/headers/InputManager.h"
#include "classes/headers/AssetManager.h"
#include "States/headers/StateMachine.h"

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
  void loadAssets();
  void run();
  void cleanup();

private:
  /* Helper Functions */
  void eventHandler(SDL_Event* event);

  CoreManagement coreManagement;
  
  bool isRunning = true;
  const float tickRate = 30.f;
  const float frameRate = 60.f;
  const float frameTime = 1000.f / this->tickRate;
};