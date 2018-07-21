#include "Entity.h"

class Component {
public:
  Component(Entity* owner);
  Component();
  ~Component();

protected:
  Entity* getOwner() const;

private:
  Entity* owner;
};