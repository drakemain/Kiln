#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include <string>
#include <map>

class AssetManager {
public:
  AssetManager();
  ~AssetManager();

  bool init();

  // load an image as a sprite and instert it into the sprite map
  Texture* loadTexture(std::string path, std::string name, SDL_Renderer* renderer);
  // fetch a texture by name from the map
  Texture* fetchTexture(std::string name);
  // destructs the texture and removes it from the map
  void unloadTexture(std::string name);

  // load a font from a file and store it in the font map
  TTF_Font* loadFont(std::string path, std::string name);

private:
  std::map<std::string, Texture*> TextureMap;
  std::map<std::string, TTF_Font*> FontMap;
};