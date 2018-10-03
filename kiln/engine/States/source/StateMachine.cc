#include "../headers/StateMachine.h"
#include <iostream>

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {

}

void StateMachine::pushState(std::unique_ptr<State> state) {
  this->isAdding = true;
  std::cout << "PUSH STATE" << std::endl;
  this->stateBuffer = std::move(state);
  std::cout << "PUSH STATE" << std::endl;
}

void StateMachine::pushForce(std::unique_ptr<State> state) {
  if (!this->empty()) {
    this->stateStack.top()->pause();
  }

  this->stateStack.push(std::move(state));
  this->stateStack.top()->init();
}

void StateMachine::replaceState(std::unique_ptr<State> state) {
  this->isRemoving = true;
  this->isAdding = true;

  this->stateBuffer = std::move(state);
}

void StateMachine::popState() {
  this->isRemoving = true;
}

void StateMachine::update() {
  if (this->isRemoving) {
    std::cout << "Removing state." << std::endl;
  }
  if (this->stateStack.empty()) {
    std::cout << "Not empty." << std::endl;
  }

  if (this->isRemoving && !this->stateStack.empty()) {
    std::cout << "REM" << std::endl;
    this->stateStack.top()->cleanup();
    this->stateStack.pop();

    if (!this->stateStack.empty()) {
      this->stateStack.top()->resume();
    }

    this->isRemoving = false;
  }

  if (this->isAdding && this->stateBuffer != nullptr) {
    this->isAdding = false;

    if (!this->empty()) {
      this->stateStack.top()->pause();
    }

    this->stateStack.push(std::move(this->stateBuffer));

    if (!this->empty()) {
      this->stateStack.top()->init();
    }
  }
}

std::unique_ptr<State>& StateMachine::getActiveState() {
  return this->stateStack.top();
}

bool StateMachine::empty() {
  return this->stateStack.empty();
}