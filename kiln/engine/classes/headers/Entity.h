#pragma once

struct Coordinate {
  int x = 0;
  int y = 0;
};

// Entities are objects that have
// a position within the game
class Entity {
public:
  virtual ~Entity();

  Coordinate getWorldPosition() const;
  void setWorldPosition(int x, int y);

  // virtual void tick(float deltaTime);
private:
  Coordinate worldPosition;
};