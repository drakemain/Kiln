#include "../headers/StateMachine.h"
#include <iostream>

StateMachine::StateMachine() {

}

StateMachine::~StateMachine() {

}

void StateMachine::pushState(std::unique_ptr<State> state) {
  this->isAdding = true;
  this->stateBuffer = std::move(state);
}

void StateMachine::pushForce(std::unique_ptr<State> state) {
  std::cout << "Force push state!" << std::endl;

  if (!this->empty()) {
    this->stateStack.top()->pause();
  }

  this->stateStack.push(std::move(state));
  this->stateStack.top()->init();
}

void StateMachine::popState() {
  std::cout << "POPPING STATE" << std::endl;
  this->isRemoving = true;
}

void StateMachine::update() {
  if (this->isRemoving && !this->stateStack.empty()) {
    std::cout << "Removing state." << std::endl;
    this->stateStack.pop();

    if (!this->stateStack.empty()) {
      this->stateStack.top()->resume();
    }

    this->isRemoving = false;
  }

  if (this->isAdding && this->stateBuffer != nullptr) {
    this->isAdding = false;
    std::cout << "Adding state." << std::endl;

    if (!this->empty()) {
      this->stateStack.top()->pause();
      std::cout << "Paused previous state." << std::endl;
    }

    this->stateStack.push(std::move(this->stateBuffer));

    std::cout << "Moved from buffer." << std::endl;
    if (!this->empty()) {
      this->stateStack.top()->init();
    }
    std::cout << "Operation complete." << std::endl;
  }
}

std::unique_ptr<State>& StateMachine::getActiveState() {
  return this->stateStack.top();
}

bool StateMachine::empty() {
  return this->stateStack.empty();
}