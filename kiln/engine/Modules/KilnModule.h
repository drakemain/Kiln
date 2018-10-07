#pragma once
#include <map>
#include <iostream>
#include "kiln/engine/States/headers/StateMachine.h"
#include "kiln/engine/Classes/headers/Sprite.h"

class KilnModule {
public:
  KilnModule();
  ~KilnModule();

  virtual bool init();

  virtual void start();
  virtual void handleEvent(SDL_Event* event);
  virtual void tick(float deltaTime);
  virtual void render();

  void bind(class Kiln* engine);

  Sprite* createSprite(std::string textureName);

  Sprite* fetchSprite(std::string name);

  void updateSubState();

  bool hasSub();

  void loadSub(class ModuleSub* sub);
  void replaceCurrentSub(class ModuleSub* sub);
  void unloadSub();

private:
  void loadSubAssets(class ModuleSub* sub);
  void unloadSubAssets(class ModuleSub* sub);

  std::map<std::string, Sprite*> spriteMap;
  StateMachine subState;
  class Kiln* engine;
};