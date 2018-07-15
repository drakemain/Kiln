#pragma once
#include <SDL.h>

// all Kiln classes should derive from this class
class Base {
protected: 
  void setBaseRenderer(SDL_Renderer* renderer);
  static void destroyBaseRenderer();
  SDL_Renderer* getBaseRenderer() const;

private:
  static SDL_Renderer* renderer;
  // static AssetManager* assetManager;
};


struct Coordinate {
  int x = 0;
  int y = 0;
};