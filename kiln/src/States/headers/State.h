#pragma once
#include <SDL.h>

class State {
public:
  virtual void init() = 0;
  virtual void cleanup() = 0;

  virtual void pause() = 0;
  virtual void resume() = 0;
  
  virtual void handleEvents() = 0;
  virtual void tick(float deltaTime) = 0;
  virtual void render() = 0;
};
