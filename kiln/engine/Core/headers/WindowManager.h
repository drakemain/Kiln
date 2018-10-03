#pragma once
#include <SDL.h>
#include "kiln/engine/Utils/headers/Dim.h"

class WindowManager {
public:
  bool init();
  void cleanup();

  SDL_Window* getWindow() const;
  SDL_Renderer* getRenderer() const;
  Dim getResolution() const;

  void setResolution(const Dim newRes);

private:
  void setFrameLimit(float frameLimit);

  SDL_Window* window;
  SDL_Renderer* renderer;

  unsigned int WIDTH = 640;
  unsigned int HEIGHT = 480;

  float FRAME_LIMIT = 60.f;
  float MIN_FRAME_TIME;
};