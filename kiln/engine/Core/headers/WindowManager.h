#pragma once
// #include <SDL.h>
#include "kiln/engine/Utils/headers/Dim.h"

class WindowManager {
public:
  bool init();
  void cleanup();

  class SDL_Window* getWindow() const;
  class SDL_Renderer* getRenderer() const;
  Dim getResolution() const;

  void setResolution(const Dim newRes);

private:
  void setFrameLimit(float frameLimit);

  class SDL_Window* window;
  class SDL_Renderer* renderer;

  unsigned int WIDTH = 640;
  unsigned int HEIGHT = 480;

  float FRAME_LIMIT = 60.f;
  float MIN_FRAME_TIME;
};