#pragma once
#include <SDL.h>
#include "kiln/engine/Classes/headers/Text.h"

class Stats {
public:
  Stats(unsigned int samples, bool renderText = false, TTF_Font* font = nullptr, SDL_Renderer* renderer = nullptr);
  ~Stats();

  void incrementFrameCount();
  float getFPS() const;
  Text* getText() const;

private:
  void update();

  unsigned int frames = 0;
  unsigned int fps = 0;

  unsigned int sampleFrames = 10;
  Uint32 lastUpdateTime = 0;

  bool renderText;
  Text* text = nullptr;
  SDL_Renderer* rendererRef;
};