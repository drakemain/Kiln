#include "TetrisModule.h"
#include "subs/init.h"

bool TetrisModule::init() {
    KilnModule::init();

    this->subState.pushForce(std::unique_ptr<State>(new InitSub(this)));
    return true;
}

void TetrisModule::start() {
    KilnModule::start();
}

void TetrisModule::handleEvent(SDL_Event* event) {
    KilnModule::handleEvent(event);
}

void TetrisModule::tick(float deltaTime) {
    KilnModule::tick(deltaTime);
}

void TetrisModule::render() {
    KilnModule::render();
}