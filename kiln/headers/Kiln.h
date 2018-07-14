#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Base.h"
#include "WindowManager.h"
#include "InputManager.h"

class Kiln : public Base {
public:
  bool init();
  void run();
  void cleanup();

private:
  /* Helper Functions */
  void eventHandler(SDL_Event* event);

  /* Private Members */
  WindowManager windowManager;
  InputManager inputManager;
  
  // TODO: State Manager
  bool isRunning = true;
};