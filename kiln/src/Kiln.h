#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "classes/headers/Base.h"
#include "classes/headers/Sprite.h"
#include "classes/headers/WindowManager.h"
#include "classes/headers/InputManager.h"
#include "classes/headers/AssetManager.h"

class Kiln : public Base {
public:
  bool init();
  void loadAssets();
  void run();
  void cleanup();

private:
  /* Helper Functions */
  void eventHandler(SDL_Event* event);

  /* Private Members */
  WindowManager windowManager;
  InputManager inputManager;
  AssetManager assetManager;
  
  // TODO: State Manager
  bool isRunning = true;
};