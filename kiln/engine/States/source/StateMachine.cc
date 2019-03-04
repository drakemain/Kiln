#include "../headers/StateMachine.h"
#include "lib/kilnlog/include/KilnLog.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {

}

void StateMachine::pushState(std::unique_ptr<State> state) {
  KLog.put(KLOG_DEB, "STATE MACHINE: PUSH");
  
  this->isAdding = true;
  this->stateBuffer = std::move(state);
}

void StateMachine::pushForce(std::unique_ptr<State> state) {
  KLog.put(KLOG_DEB, "STATE MACHINE: PUSH FORCE");

  if (!this->empty()) {
    this->stateStack.top()->pause();
  }

  this->stateStack.push(std::move(state));
  this->stateStack.top()->init();
}

void StateMachine::replaceState(std::unique_ptr<State> state) {
  KLog.put(KLOG_DEB, "STATE MACHINE: REPLACE");

  this->isRemoving = true;
  this->isAdding = true;

  this->stateBuffer = std::move(state);
}

void StateMachine::popState() {
  KLog.put(KLOG_DEB, "STATE MACHINE: REMOVE");
  this->isRemoving = true;
}

void StateMachine::update() {
  if (this->isRemoving && !this->stateStack.empty()) {
    KLog.put(KLOG_DEB, "State machine is removing top.");
    this->stateStack.top()->cleanup();
    this->stateStack.pop();

    if (!this->stateStack.empty()) {
      this->stateStack.top()->resume();
    }

    this->isRemoving = false;
  }

  if (this->isAdding && this->stateBuffer != nullptr) {
    KLog.put(KLOG_DEB, "State machine is adding new state.");
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