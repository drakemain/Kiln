#pragma once
#include "kiln/engine/Modules/ModuleSub.h"
#include <iostream>

class InitSub : public ModuleSub {
public:
    InitSub(class KilnModule* mod) :ModuleSub(mod) { 
        this->module->createSprite("kiln/assets/img/button-bg.png", "btn");
        std::cout << "INITSUB CONST!!" << std::endl;
    }
    void init() override { std::cout << "INITSUB INIT!!" << std::endl; }
    void cleanup() override {}
    void pause() override {}
    void resume() override {}
    void handleEvent(SDL_Event* event) override {}
    void tick(float deltaTime) override {}
    void render() override {
        std::cout << "Rendering!" << std::endl;
        this->module->fetchSprite("btn")->render(this->module->window->getRenderer());
    }
};