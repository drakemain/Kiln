#pragma once
#include <SDL.h>
#include "Modules/KilnModule.h"
#include "Core/headers/WindowManager.h"
#include "Core/headers/InputManager.h"
#include "Core/headers/AssetManager.h"
#include "kiln/engine/Classes/headers/Text.h"
#include "Core/headers/Stats.h"

struct CoreManagement {
  WindowManager windowManager;
  InputManager inputManager;
  AssetManager assetManager;
};

class Kiln {
public:
  Kiln();
  // ~Kiln();
  
  bool init(KilnModule& module);
  void run(KilnModule& module);
  void cleanup();

  CoreManagement* getManagement() {return &this->coreManagement;}

private:
  /* Helper Functions */
  void checkQuit(SDL_Event* event);
  void tick(float deltaTime);
  void render();

  CoreManagement coreManagement;
  
  bool isRunning = true;

  Stats* stats;
};