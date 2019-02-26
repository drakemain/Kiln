#pragma once

class Timer {
public:
  void start();
  void pause();
  void reset();
  
  float getTime() const;

  void tick(float deltaTime);

private:
  float time = 0.f;
  bool isRunning = false;
};