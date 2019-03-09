#pragma once

#include <SDL_ttf.h>
#include "kiln/engine/Classes/Entity/headers/Entity.h"

class Stats: public Entity {
public:
  Stats(unsigned int samples, bool renderText = false, TTF_Font* font = nullptr, SDL_Renderer* renderer = nullptr);
  ~Stats();

  void tick(float deltaTime) override;
  void start() override;

  void incrementFrameCount();
  float getFPS() const;
  class TextComponent* getText() const;

private:
  void update();

  unsigned int frames = 0;
  float fps = 0;

  unsigned int sampleFrames = 100;

  bool renderText;
  class TextComponent* text = nullptr;
  SDL_Renderer* rendererRef;

  class Timer* timer;
};