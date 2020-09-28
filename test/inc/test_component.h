#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "game_component.h"
#include "sprite.h"
#include <memory>

class TestComponent : public GameComponent
{
public:

TestComponent() : GameComponent()
  {}

  virtual std::vector<std::unique_ptr<Sprite>>& get_render_components() = 0;

};

#endif
