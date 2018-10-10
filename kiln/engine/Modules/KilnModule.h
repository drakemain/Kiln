#pragma once
#include <map>
#include <iostream>
#include "kiln/engine/States/headers/StateMachine.h"
#include "kiln/engine/Classes/headers/Sprite.h"
#include "SDL_ttf.h"

class KilnModule {
public:
  KilnModule();
  ~KilnModule();

  /* Kiln Interface */
  virtual bool init();
  virtual void start();
  virtual void handleEvent(SDL_Event* event);
  virtual void tick(float deltaTime);
  virtual void render();
  void updateSubState();
  bool hasSub();

  /* Get reference to engine instance */
  void bind(class Kiln* engine);

  /* Assets Interface */
  Sprite* createSprite(std::string textureName);
  Sprite* fetchSprite(std::string name);
  Texture* fetchTexture(std::string name);
  TTF_Font* fetchFont(std::string name);
  void playSound(std::string soundName, int loops);
  void playMusic(std::string musicName);
  SDL_Renderer* getRenderer();

  /* Submodule methods */
  void loadSub(class ModuleSub* sub);
  void replaceCurrentSub(class ModuleSub* sub);
  void unloadSub();
  void quit();

private:
  void loadSubAssets(class ModuleSub* sub);
  void unloadSubAssets(class ModuleSub* sub);

  std::map<std::string, Sprite*> spriteMap;
  StateMachine subState;
  class Kiln* engine;

  bool unwindStack = false;
};