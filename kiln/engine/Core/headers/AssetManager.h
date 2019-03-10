#pragma once
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <map>

class AssetManager {
public:
  AssetManager();
  ~AssetManager();

  bool init(class SDL_Renderer*, const struct AssetConfig&);

  // load a texture that won't be managed by the asset manager
  class Texture* loadTexture(const char* path, const char* identifier);
  // fetch a texture by name from the map
  class Texture* fetchTexture(const char* identifier);
  // destructs the texture and removes it from the map
  void unloadTexture(const char* identifier);

  // load a font from a file and store it in the font map
  TTF_Font* loadFont(const char* path, int size, const char* identifier);
  // fetch a font from the font map
  TTF_Font* fetchFont(const char* identifier);
  // destruct and remove a font
  void unloadFont(const char* identifier);

  Mix_Music* loadMusic(const char* path, const char* identifier);
  Mix_Music* fetchMusic(const char* identifier);
  void unloadMusic(const char* identifier);

  Mix_Chunk* loadSound(const char* path, const char* identifier);
  Mix_Chunk* fetchSound(const char* identifier);
  void unloadSound(const char* identifier);

private:
  Texture* loadTexture(const char* path);
  TTF_Font* loadFont(const char* path, int size);
  Mix_Music* loadMusic(const char* path);
  Mix_Chunk* loadSound(const char* path);

  bool loadPlaceholders();

  std::map<const char*, Texture*> TextureMap;
  std::map<const char*, TTF_Font*> FontMap;
  std::map<const char*, Mix_Music*> MusicMap;
  std::map<const char*, Mix_Chunk*> SoundMap;

  Texture* placeholderTexture = nullptr;
  TTF_Font* placeholderFont = nullptr;
  Mix_Music* placeholderMusic = nullptr;
  Mix_Chunk* placeholderSound = nullptr;

  class SDL_Renderer* renderer;
};