#pragma once
#include <SDL_ttf.h>
#include <string>

class KilnModule {
  friend class Kiln;
public:
  KilnModule();
  ~KilnModule();

protected:
  /* Kiln Interface */
  virtual bool init();
  virtual void start();
  virtual void handleEvent(const SDL_Event* event);
  virtual void tick(float deltaTime);
  virtual void render(struct SDL_Renderer* renderer);

private:
  void updateSubState();
  bool hasSub();

  /* Get reference to engine instance */
  void bind(class Kiln* engine);

public:
  /* Assets Interface */
  void bindEntity(class Entity* entity);
  void bindEventComponent(class EventComponent* component);
  void bindInput(Uint8, void(*)(void));
  class Texture* fetchTexture(const char* name);
  TTF_Font* fetchFont(const char* name);
  void playSound(const char* soundName, int loops);
  void playMusic(const char* musicName);
  class SDL_Renderer* getRenderer();

public:
  /* Submodule methods */
  void loadSub(class SubModule* sub);
  void replaceCurrentSub(class SubModule* sub);
  void unloadSub();
  void quit();

private:
  void loadSubAssets(class SubModule& sub);
  void unloadSubAssets(class SubModule* sub);

  class StateMachine* subState;
  class EventManager* eventManager;
  class Kiln* engine;

  bool unwindStack = false;
};