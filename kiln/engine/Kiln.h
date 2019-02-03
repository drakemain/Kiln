#pragma once

#include "Core/headers/WindowManager.h"
#include "Core/headers/InputManager.h"
#include "Core/headers/AssetManager.h"

struct CoreManagement {
  WindowManager windowManager;
  InputManager inputManager;
  AssetManager assetManager;
};

class Kiln {
public:
  Kiln();
  ~Kiln();
  
  bool init(class KilnModule& module);
  void run(class KilnModule& module);
  void cleanup();

  CoreManagement* getManagement() {return &this->coreManagement;}

private:
  /* Helper Functions */
  void checkEngineEvent(SDL_Event* event);
  void tick(float deltaTime);
  void render(SDL_Renderer* renderer);

  CoreManagement coreManagement;
  
  bool isRunning = true;

  class Stats* stats;
};