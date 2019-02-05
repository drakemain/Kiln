#include "../headers/init.h"
#include "kiln/engine/Classes/Menu/headers/Button.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Definitions/Colors.h"
#include "kiln/TetrisModule/subs/headers/mainmenu.h"
#include "kiln/engine/Classes/headers/Sprite.h"

InitSub::InitSub(class KilnModule* mod) : ModuleSub(mod) {
  std::cout << "Loaded init sub" << std::endl;

  this->assetDependencies.textures = {
    {"kiln/assets/img/button-bg.png", "btn"}
  };

  this->assetDependencies.fonts = {
    {{"kiln/assets/font/RobotoMono-Regular.ttf", "btn"}, 128}
  };

  this->assetDependencies.sounds = {
    {"kiln/assets/audio/sounds/win98.wav", "win98"}
  };
}

void InitSub::init() {
  this->module->playSound("win98", 0);
  TTF_Font* buttonFont = this->module->fetchFont("btn");
  Texture* buttonTexture = this->module->fetchTexture("btn");
  SDL_Renderer* renderer = this->module->getRenderer();

  Button* button = new Button(buttonTexture, "Button", buttonFont, KILN_COLOR::ORANGE, renderer);
  Sprite* sprite = new Sprite(this->module->fetchTexture("btn"));
  
  this->registerEntity(button);
  this->registerEntity(sprite);

  sprite->scale(.3);
  sprite->setWorldPosition({50, 50});
  
  std::cout << "Setting Button Position" << std::endl;
  button->setWorldPosition(50.f, 50.f);
  button->scale(.5);

  button->bindAction([this](){this->module->loadSub(new MainMenu(this->module));});

  button->start();
}

void InitSub::cleanup() {}
void InitSub::pause() {}
void InitSub::resume() {}
void InitSub::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.clicks == SDL_BUTTON_LEFT) {
      ICoordinate coord;
      SDL_GetMouseState(&coord.x, &coord.y);
      // this->button->checkWasClicked(coord);
      // this->button->setWorldPosition((float)coord.x, (float)coord.y);
    }
  }
}

void InitSub::tick(float deltaTime) {
  ModuleSub::tick(deltaTime);
  this->runtime += deltaTime;
  // if (this->runtime > 3000) {
  //   this->module->unloadSub();
  // }
}

void InitSub::render(SDL_Renderer* renderer) {
  ModuleSub::render(renderer);
  // this->testSprite->render(renderer);
}