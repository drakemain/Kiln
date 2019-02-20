#pragma once
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

class Texture;

class AssetManager {
public:
  AssetManager();
  ~AssetManager();

  bool init(SDL_Renderer* renderer, const struct AssetConfig&);

  // load an image as a Texture and instert it into the sprite map
  Texture* loadTexture(std::string path, std::string name, SDL_Renderer* renderer);
  // load a texture that won't be managed by the asset manager
  Texture* loadTexture(std::string path, SDL_Renderer* renderer);
  // fetch a texture by name from the map
  Texture* fetchTexture(std::string name);
  // destructs the texture and removes it from the map
  void unloadTexture(std::string name);

  // load a font from a file and store it in the font map
  TTF_Font* loadFont(std::string path, int size, std::string name);
  // load a font that won't be managed by the asset manager
  TTF_Font* loadFont(std::string path, int size);
  // fetch a font from the font map
  TTF_Font* fetchFont(std::string name);
  // destruct and remove a font
  void unloadFont(std::string name);

  Mix_Music* loadMusic(std::string path, std::string name);
  Mix_Music* loadMusic(std::string path);
  Mix_Music* fetchMusic(std::string name);
  void unloadMusic(std::string name);

   Mix_Chunk* loadSound(std::string path, std::string name);
   Mix_Chunk* loadSound(std::string path);
   Mix_Chunk* fetchSound(std::string name);
  void unloadSound(std::string name);

private:
  std::map<std::string, Texture*> TextureMap;
  std::map<std::string, TTF_Font*> FontMap;
  std::map<std::string, Mix_Music*> MusicMap;
  std::map<std::string, Mix_Chunk*> SoundMap;
};