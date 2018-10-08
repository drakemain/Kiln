#include "../headers/Menu.h"
#include "kiln/engine/Definitions/Colors.h"
#include <iostream>

Menu::Menu(CoreManagement& core)
: core(core) {}

void Menu::init() {
  SDL_Renderer* renderer = this->core.windowManager.getRenderer();
  Dim windowSize = this->core.windowManager.getResolution();
  
  Texture* spriteTexture = this->core.assetManager.loadTexture("kiln/assets/img/sprite-test2.jpg", "SpriteTexture", renderer);
  Texture* buttonTexture = this->core.assetManager.loadTexture("kiln/assets/img/button-bg.png", "ButtonTexture", renderer);

  this->staticElements.push_back(new Sprite(spriteTexture));
  this->buttons.push_back(new Button(buttonTexture));

  this->buttons[0]->centerInWindow(windowSize.w, windowSize.h);
}

void Menu::cleanup() {
  for (Sprite* elem : this->staticElements) {
    delete elem;
  }

  for (Button* button : this->buttons) {
    delete button;
  }

  this->core.assetManager.unloadTexture("SpriteTexture");
  this->core.assetManager.unloadTexture("ButtonTexture");
}

void Menu::pause() {}
void Menu::resume() {}

void Menu::handleEvent(SDL_Event* event) {
  // if (event) {
  //   if (event->type == SDL_MOUSEBUTTONDOWN) {
  //     if (event->button.button == SDL_BUTTON_LEFT) {
  //       ICoordinate clickPos = this->core.inputManager.getCursorClickedPosition();

  //       for (Button* button : this->buttons) {
  //         // if (button->wasClicked(clickPos)) {
  //         //   std::cout << "BUTTON CLICK" << std::endl;
  //         //   break;
  //         // }
  //       }
  //     }
  //   }
  // }
}

void Menu::tick(float deltaTime) {
  this->runTime += deltaTime;
}

void Menu::render() {
  SDL_Renderer* renderer = this->core.windowManager.getRenderer();
  SDL_SetRenderDrawColor(renderer, 0xA9, 0xA9, 0xA9, 0xFF);

  for (Sprite* elem : this->staticElements) {
    elem->render(renderer);
  }
  
  for (Button* button : this->buttons) {
    button->render(renderer);
  }
}