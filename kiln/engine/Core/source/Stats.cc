#include "../headers/Stats.h"
#include <iostream>
#include "kiln/engine/Definitions/Colors.h"

Stats::Stats(unsigned int samples, bool renderText, TTF_Font* font, SDL_Renderer* renderer) 
: sampleFrames(samples), renderText(renderText), rendererRef(renderer) {
  if (renderText && font && renderer) {
    this->text = new Text("0.0", font, KILN_COLOR::ORANGE, renderer);
  } else {
    std::cerr << "Stats wanted to render text but was missing a font or renderer." << std::endl;
    this->renderText = false;
  }
}

Stats::~Stats() {
  delete this->text;
}

void Stats::incrementFrameCount() {
  if (++this->frames >= this->sampleFrames) {
    this->update();
  }
}

float Stats::getFPS() const {
  return this->fps;
}

Text* Stats::getText() const {
  return this->text;
}

void Stats::update() {
  Uint32 interval = SDL_GetTicks() - this->lastUpdateTime;

  this->fps = (frames * 1000) / interval;

  if (this->renderText && this->rendererRef) {
    this->text->setText(std::to_string(this->fps));
    this->text->draw(this->rendererRef);
  }

  this->frames = 0;
  this->lastUpdateTime = SDL_GetTicks();
}