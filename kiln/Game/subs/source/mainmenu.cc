#include "kiln/Game/subs/headers/mainmenu.h"
#include "kiln/engine/Module/KilnModule.h"
#include "kiln/engine/Classes/Menu/headers/Button.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Definitions/Colors.h"

MainMenu::MainMenu(KilnModule* module)
: Menu(module) {
  this->assetDependencies.textures = {
    {"kiln/assets/img/button-bg.png", "btn"}
  };

  this->assetDependencies.sounds = {
    {"kiln/assets/audio/sounds/win98.wav", "win98"}
  };
}

void MainMenu::init() {
  Texture* buttonTexture = this->module->fetchTexture("btn");
  TTF_Font* buttonFont = this->module->fetchFont("StatsFont");
  SDL_Renderer* renderer = this->module->getRenderer();
  FCoordinate textPosition;

  Button* exitButton = new Button(buttonTexture, "Exit", buttonFont, KILN_COLOR::DARK_GREY, renderer);
  exitButton->centerInWindow(640, 480);
  exitButton->bindAction([this](){this->module->quit();});
  exitButton->getTextComponent()->setRelativePosition(textPosition);

  exitButton->scale(.75);

  this->createButton(exitButton);
}

void MainMenu::cleanup() {}

void MainMenu::pause() {}

void MainMenu::resume() {}

void MainMenu::handleEvent(SDL_Event* event) {
  Menu::handleEvent(event);
}

void MainMenu::tick(float deltaTime) {
  Menu::tick(deltaTime);
}

void MainMenu::render(SDL_Renderer* renderer) {
  Menu::render(renderer);
}