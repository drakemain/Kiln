#include "../headers/Menu.h"
#include "kiln/engine/Definitions/Colors.h"
#include "kiln/engine/Modules/KilnModule.h"
#include "kiln/engine/Classes/Menu/headers/Button.h"
#include <iostream>

Menu::Menu(KilnModule* module)
: ModuleSub(module) {}

// void Menu::cleanup() {
//   // for (Sprite* elem : this->staticElements) {
//   //   delete elem;
//   // }

//   // for (Button* button : this->buttons) {
//   //   delete button;
//   // }

//   // this->core.assetManager.unloadTexture("SpriteTexture");
//   // this->core.assetManager.unloadTexture("ButtonTexture");
// }

// void Menu::pause() {}
// void Menu::resume() {}

void Menu::handleEvent(SDL_Event* event) {
  if (event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
      if (event->button.button == SDL_BUTTON_LEFT) {
        ICoordinate clickPos;
        SDL_GetMouseState(&clickPos.x, &clickPos.y);

        for (Button* button : this->buttons) {
          button->checkWasClicked(clickPos);
        }
      }
    }
  }
}

void Menu::tick(float deltaTime) {
  this->runTime += deltaTime;
}

void Menu::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0xA9, 0xA9, 0xA9, 0xFF);

  for (Entity* elem : this->staticElements) {
    elem->render(renderer);
  }
  
  for (Button* button : this->buttons) {
    button->render(renderer);
  }
}

void Menu::createButton(Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
  Button* button = new Button(texture, text, font, color, renderer);

  this->buttons.push_back(button);
}

void Menu::createButton(Texture* texture) {
  Button* button = new Button(texture);

  this->buttons.push_back(button);
}

void Menu::createButton(Button* button) {
  this->buttons.push_back(button);
}

void Menu::createStatic(Entity* entity) {
  this->staticElements.push_back(entity);
}