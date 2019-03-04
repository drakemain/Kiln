#pragma once
#include <SDL_ttf.h>
#include <string>

class KilnModule {
public:
  KilnModule();
  ~KilnModule();

  /* Kiln Interface */
  virtual bool init();
  virtual void start();
  virtual void handleEvent(const SDL_Event* event);
  virtual void tick(float deltaTime);
  virtual void render();
  void updateSubState();
  bool hasSub();

  /* Get reference to engine instance */
  void bind(class Kiln* engine);

  /* Assets Interface */
  void bindEntity(class Entity* entity);
  void bindEventComponent(class EventComponent* component);
  void bindInput(Uint8, void(*)(void));
  class Texture* fetchTexture(std::string name);
  TTF_Font* fetchFont(std::string name);
  void playSound(std::string soundName, int loops);
  void playMusic(std::string musicName);
  class SDL_Renderer* getRenderer();

  /* Submodule methods */
  void loadSub(class SubModule* sub);
  void replaceCurrentSub(class SubModule* sub);
  void unloadSub();
  void quit();

private:
  void loadSubAssets(class SubModule& sub);
  void unloadSubAssets(class SubModule* sub);

  class StateMachine* subState;
  class LayerManager* layerManager;
  class EventManager* eventManager;
  class Kiln* engine;

  bool unwindStack = false;
};