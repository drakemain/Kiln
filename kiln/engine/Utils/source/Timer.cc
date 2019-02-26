#include "../headers/Timer.h"

void Timer::start() {
  this->isRunning = true;
}

void Timer::pause() {
  this->isRunning = false;
}

void Timer::reset() {
  this->time = 0.f;
}

float Timer::getTime() const {
  return this->time;
}

void Timer::tick(float deltaTime) {
  if (this->isRunning) {
    this->time += deltaTime;
  }
}