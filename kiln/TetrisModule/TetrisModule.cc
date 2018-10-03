#include "TetrisModule.h"
#include "subs/init.h"

bool TetrisModule::init() {
    KilnModule::init();
    
    std::cout << "Tetris Module" << std::endl;
    this->subState.pushForce(std::unique_ptr<State>(new InitSub(this)));
    std::cout << "Tetris Module" << std::endl;
    return true;
}

void TetrisModule::start() {

}

void TetrisModule::handleEvent(SDL_Event* event) {

}

void TetrisModule::tick(float deltaTime) {

}

void TetrisModule::render() {
    KilnModule::render();
}