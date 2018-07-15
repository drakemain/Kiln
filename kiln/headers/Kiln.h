#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Base.h"
#include "Sprite.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "AssetManager.h"

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