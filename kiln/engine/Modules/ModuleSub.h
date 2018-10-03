#pragma once
#include "kiln/engine/States/headers/State.h"

class ModuleSub : public State {
public:
    ModuleSub(class KilnModule* mod) : module(mod) {}
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;
    
    virtual void handleEvent(SDL_Event* event) = 0;
    virtual void tick(float deltaTime) = 0;
    virtual void render() = 0;

    class KilnModule* module;
};