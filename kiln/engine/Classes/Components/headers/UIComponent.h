#pragma once
#include "Component.h"

enum Anchor {
  TopLeft,
  Left,
  BottomLeft,
  Bottom,
  BottomRight,
  Right,
  TopRight,
  Top,
  None
};

class UIComponent : Component {
public:
  UIComponent(class Entity* owner);

  void setAnchor(Anchor anchor);
  void reposition();

private:
  Anchor anchor = Anchor::None;
};