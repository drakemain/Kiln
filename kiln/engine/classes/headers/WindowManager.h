#pragma once
#include <SDL.h>

class WindowManager {
public:
  bool init();
  void cleanup();

  SDL_Window* getWindow() const;
  SDL_Renderer* getRenderer() const;

private:
  void setFrameLimit(float frameLimit);

  SDL_Window* window;
  SDL_Renderer* renderer;

  unsigned int WIDTH = 640;
  unsigned int HEIGHT = 480;

  float FRAME_LIMIT = 60.f;
  float MIN_FRAME_TIME;
};