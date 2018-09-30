#include "test.h"
#include <iostream>

bool Test::init() {
    std::cout << "TEST INIT" << std::endl;
    this->assets->loadSound("kiln/assets/audio/sounds/win98.wav", "win98");
    this->createSprite("kiln/assets/img/button-bg.png", "button");
    return true;
}

void Test::start() {
    Mix_PlayChannel(-1, this->assets->fetchSound("win98"), 0);
}

void Test::handleEvent(SDL_Event* event) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->fetchSprite("button")->setWorldPosition(x, y);
    }
}

void Test::render() {
    this->fetchSprite("button")->render(this->window->getRenderer());
}
