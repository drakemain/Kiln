#pragma once

#include "kiln/engine/Utils/headers/Dim.h"
#include <string>

class WindowManager {
public:
  bool init(const struct WindowConfig&);
  void cleanup();

  class SDL_Window* getWindow() const;
  class SDL_Renderer* getRenderer() const;
  Dim getResolution() const;

  void setResolution(const Dim newRes);

private:
  void setFrameLimit(float frameLimit);

  class SDL_Window* window;
  class SDL_Renderer* renderer;

  std::string title;

  unsigned int WIDTH;
  unsigned int HEIGHT;

  float FRAME_LIMIT = 60.f;
  float MIN_FRAME_TIME;
};