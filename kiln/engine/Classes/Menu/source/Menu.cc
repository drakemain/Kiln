#include "../headers/Menu.h"
#include "kiln/engine/Definitions/Colors.h"

Menu::Menu(CoreManagement& core)
: core(core) {}

void Menu::init() {
  SDL_Renderer* renderer = this->core.windowManager.getRenderer();
  Texture* texture = this->core.assetManager.loadTexture("kiln/assets/img/sprite-test2.jpg", "SpriteTexture", renderer);
  Sprite* sprite = new Sprite(texture);
  // sprite->set

  this->staticElements.push_back(sprite);
}

void Menu::cleanup() {
  for (Sprite* elem : this->staticElements) {
    delete elem;
  }
}

void Menu::pause() {}
void Menu::resume() {}

void Menu::handleEvents() {}
void Menu::tick(float deltaTime) {
  this->runTime += deltaTime;
}
void Menu::render() {
  SDL_Renderer* renderer = this->core.windowManager.getRenderer();
  SDL_SetRenderDrawColor(renderer, 0xA9, 0xA9, 0xA9, 0xFF);

  for (Sprite* elem : this->staticElements) {
    elem->render(renderer);
  }
}