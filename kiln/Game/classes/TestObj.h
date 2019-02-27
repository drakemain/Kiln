#pragma once

#include "kiln/engine/Classes/Entity/headers/Sprite.h"
#include "kiln/engine/Classes/Components/headers/InputComponent.h"
#include "kiln/engine/Classes/Components/headers/MovementComponent.h"
#include "kiln/engine/Classes/Components/headers/CollisionComponent.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Utils/headers/Timer.h"
#include "kiln/engine/Definitions/Colors.h"

class TestObj : public Sprite {
public:
  TestObj(Texture* texture, TTF_Font* font, SDL_Renderer* renderer): Sprite(texture) {
    this->input = new InputComponent();
    this->movement = new MovementComponent();
    this->collision = new CollisionComponent();
    this->velocityText = new TextComponent("", font, renderer, KILN_COLOR::WHITE);
    this->accelTime = new TextComponent("", font, renderer, KILN_COLOR::WHITE);

    this->timer = new Timer();

    this->input->bind(SDLK_UP, [this](){this->movement->consumeDirection(Direction::Up);});
    this->input->bind(SDLK_DOWN, [this](){this->movement->consumeDirection(Direction::Down);});
    this->input->bind(SDLK_RIGHT, [this](){this->movement->consumeDirection(Direction::Right);});
    this->input->bind(SDLK_LEFT, [this](){this->movement->consumeDirection(Direction::Left);});

    this->velocityText->setScale(.35);
    this->accelTime->setScale(.25);

    this->bindComponent(input);
    this->bindComponent(movement);
    this->bindComponent(collision);
    this->bindComponent(velocityText);
    this->bindComponent(accelTime);
  }

  virtual void start() override {
    Sprite::start();
    this->timer->start();
    this->velocityText->setText(std::to_string(this->movement->getVelocity().magnitude()));
    this->accelTime->setRelativePosition({0.f, (float)this->velocityText->getDimensions().h});
  }

  virtual void tick(float deltaTime) override {
    Sprite::tick(deltaTime);
    this->timer->tick(deltaTime);
    this->velocityText->setText("Velocity: " + std::to_string(this->movement->getVelocity().magnitude()));
    this->accelTime->setText("Timer: " + std::to_string(this->timer->getTime()));
    // this->velocityText->setScale(((float)((int)this->timer->getTime() % 1000)/100)+.1f);

    this->accelTime->setRelativePosition({0.f, (float)this->velocityText->getDimensions().h});
  }

private:
  class InputComponent* input;
  class MovementComponent* movement;
  class CollisionComponent* collision;
  class TextComponent* velocityText;
  class TextComponent* accelTime;
  class Timer* timer;
};