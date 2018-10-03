#pragma once
#include "kiln/engine/Modules/ModuleSub.h"
#include "kiln/engine/Modules/KilnModule.h"
#include <iostream>

class InitSub : public ModuleSub {
public:
    InitSub(class KilnModule* mod) :ModuleSub(mod) { 
        this->module->createSprite("kiln/assets/img/button-bg.png", "btn");
    }
    void init() override {}

    void cleanup() override {}
    void pause() override {}
    void resume() override {}
    void handleEvent(SDL_Event* event) override {}
    void tick(float deltaTime) override {}
    void render() override {
        this->module->fetchSprite("btn")->render(this->module->window->getRenderer());
    }
};