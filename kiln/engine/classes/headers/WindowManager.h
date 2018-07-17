#pragma once
#include <SDL.h>
#include "Base.h"

class WindowManager : public Base {
public:
  bool init();
  void cleanup();

  SDL_Window* getWindow() const;

private:
  void setFrameLimit(float frameLimit);

  SDL_Window* window;

  unsigned int WIDTH = 640;
  unsigned int HEIGHT = 480;

  float FRAME_LIMIT = 60.f;
  float MIN_FRAME_TIME;
};