#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Base.h"
#include "Texture.h"
#include <string>
#include <map>

class AssetManager : public Base {
public:
  AssetManager();
  ~AssetManager();

  bool init();

  // load an image as a sprite and instert it into the sprite map
  Texture* loadTexture(std::string path, std::string name);
  // fetch a texture by name from the map
  Texture* fetchTexture(std::string name);
  // destructs the sprite and removes it from the map
  void unloadSprite(std::string name);

  // load a font from a file and store it in the font map
  TTF_Font* loadFont(std::string path, std::string name);

private:
  std::map<std::string, Texture*> TextureMap;
  std::map<std::string, TTF_Font*> FontMap;
};