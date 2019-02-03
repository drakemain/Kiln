#include "../headers/Stats.h"
#include <iostream>
#include "kiln/engine/Definitions/Colors.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"

Stats::Stats(unsigned int samples, bool renderText, TTF_Font* font, SDL_Renderer* renderer) 
: sampleFrames(samples), renderText(renderText), rendererRef(renderer) {
  if (renderText && font && renderer) {
    this->text = new TextComponent(this, "0.0", font, renderer, KILN_COLOR::ORANGE);
  } else {
    std::cerr << "Stats wanted to render text but was missing a font or renderer." << std::endl;
    this->renderText = false;
  }
}

Stats::~Stats() {}

void Stats::tick(float deltaTime) {
  this->text->tick(deltaTime);
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
  Uint32 interval = SDL_GetTicks() - this->lastUpdateTime;

  this->fps = (frames * 1000) / interval;

  if (this->renderText && this->rendererRef) {
    this->text->setText(std::to_string(this->fps));
  }

  this->frames = 0;
  this->lastUpdateTime = SDL_GetTicks();
}