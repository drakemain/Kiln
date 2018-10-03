#pragma once
#include "kiln/engine/States/headers/State.h"

class ModuleSub : public State {
public:
  ModuleSub(class KilnModule* mod) : module(mod) {}
  class KilnModule* module;
};