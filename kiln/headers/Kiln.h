#pragma once
#include <SDL.h>

class Kiln {
public:
  bool init();
  void run();
  void cleanup();

private:
  SDL_Window* window;
  const int WIDTH = 640;
  const int HEIGHT = 480;
};