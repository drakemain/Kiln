#include "../headers/Stats.h"
#include "kiln/engine/Definitions/Colors.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Utils/headers/Timer.h"

Stats::Stats(unsigned int samples, bool renderText, TTF_Font* font, SDL_Renderer* renderer) 
: sampleFrames(samples), renderText(renderText), rendererRef(renderer) {
  if (renderText && font && renderer) {
    this->text = new TextComponent("0.0", font, renderer, KILN_COLOR::ORANGE);
  } else {
    this->renderText = false;
  }

  this->bindComponent(text);
  this->timer = new Timer();
  timer->start();
}

Stats::~Stats() {
  delete this->timer;
}

void Stats::tick(float deltaTime) {
  this->text->tick(deltaTime);
  this->timer->tick(deltaTime);
}

void Stats::start() {
  
}

void Stats::incrementFrameCount() {
  if (++this->frames >= this->sampleFrames) {
    this->update();
  }
}

float Stats::getFPS() const {
  return this->fps;
}

TextComponent* Stats::getText() const {
  return this->text;
}

void Stats::update() {
  float interval = timer->getTime();
  timer->reset();

  this->fps = frames / interval;

  if (this->renderText && this->rendererRef) {
    this->text->setText("FPS: " + std::to_string(this->fps));
  }

  this->frames = 0;
}