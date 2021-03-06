#pragma once

#include "Core/headers/WindowManager.h"
#include "Core/headers/InputManager.h"
#include "Core/headers/AssetManager.h"
#include "Core/headers/SpriteManager.h"

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
  void checkEngineEvent(const SDL_Event* event);
  void tick(float deltaTime);
  void render(KilnModule& module);

  CoreManagement coreManagement;
  
  bool isRunning = true;
  bool quit = false;

  class Stats* stats = nullptr;
};