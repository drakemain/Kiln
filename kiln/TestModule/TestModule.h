#pragma once
#include "kiln/engine/Modules/KilnModule.h"
#include "kiln/engine/Classes/headers/Sprite.h"

class Test : public KilnModule {
public:
    Test() {}
    virtual bool init() override;
    virtual void start() override;
    virtual void handleEvent(SDL_Event* event) override;
    virtual void tick(float deltaTime) override {};
    virtual void render() override;
};