#include "../headers/init.h"
#include "kiln/engine/Classes/Menu/headers/Button.h"

InitSub::InitSub(class KilnModule* mod) : ModuleSub(mod) {
  std::cout << "Loaded init sub" << std::endl;

  this->assetDependencies.textures = {
    {"kiln/assets/img/button-bg.png", "btn"}
  };
  this->assetDependencies.sounds = {
    {"kiln/assets/audio/sounds/win98.wav", "win98"}
  };
}

void InitSub::init() {
  // this->module->playSound("win98", 1);

  this->button = new Button(this->module->fetchTexture("btn"));
  this->button->setScale(.25);

  this->button->bindAction([](){std::cout << "LAMBDA CLICK!" << std::endl;});
}

void InitSub::cleanup() {}
void InitSub::pause() {}
void InitSub::resume() {}
void InitSub::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.clicks == SDL_BUTTON_LEFT) {
      ICoordinate coord;
      SDL_GetMouseState(&coord.x, &coord.y);
      this->button->ifClicked(coord);
    }
  }
}

void InitSub::tick(float deltaTime) {
  this->runtime += deltaTime;

  // if (this->runtime > 3000) {
  //   this->module->unloadSub();
  // }
}
void InitSub::render(SDL_Renderer* renderer) {
  // this->module->fetchSprite("btn")->render(renderer);
  this->button->render(renderer);
}