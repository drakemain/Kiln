#include "Entity.h"

class Component {
public:
  Component(Entity* owner);

private:
  Entity* owner;
};