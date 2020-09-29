#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "game_component.h"
#include "input_event.h"
#include "sprite.h"
#include <memory>
#include <functional>

class TestComponent : public GameComponent
{
public:

  TestComponent() : GameComponent()
  {
    update_delegate = []{};  
  }

  virtual void update() override
  {
    update_delegate();
  }

  virtual void update( InputEvent& event ) override
  {
  }

  virtual std::vector<std::unique_ptr<Sprite>>& get_render_components() = 0;

  virtual void on_update( std::function<void()> on_update )
  {
    update_delegate = on_update;
  }

private:
  
  std::function<void()> update_delegate;

};

#endif
