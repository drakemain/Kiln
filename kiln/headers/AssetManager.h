#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Base.h"
#include "Sprite.h"
#include <string>
#include <map>

class AssetManager : public Base {
public:
  AssetManager();
  ~AssetManager();

  // load an image as a texture and instert it into the map
  Sprite* loadSprite(std::string path, std::string name);
  // fetch a texture by name from the map
  Sprite* fetchSprite(std::string name);
  // destructs the sprite and removes it from the map
  void unloadSprite(std::string name);

private:
  std::map<std::string, Sprite*> SpriteMap;
};