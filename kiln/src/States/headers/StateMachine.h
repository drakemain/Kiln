#pragma once
#include "State.h"
#include <stack>
#include <memory>

class StateMachine {
public:
  StateMachine();
  ~StateMachine();

  void pushState(std::unique_ptr<State> state);
  void pushForce(std::unique_ptr<State> state);
  void popState();

  void update();

  std::unique_ptr<State>& getActiveState();

  bool empty();

private:
  std::stack<std::unique_ptr<State>> stateStack;
  std::unique_ptr<State> stateBuffer;

  bool isRemoving = false;
  bool isAdding = false;
  // bool isReplacing;
};