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
    origin = std::make_unique<WorldCoordinates>( 0, 0 );
  }

  virtual std::vector<std::unique_ptr<Sprite>>& get_render_components() = 0;

  virtual void on_update( std::function<void()> on_update ) override
  {
    update_delegate = on_update;
  }

  virtual void update() override
  {
    update_delegate();
  }

  virtual void update( InputEvent& event ) override
  {
    update_delegate();
  }

  virtual bool accepting_input() override
  {
    return false;
  }

  virtual int get_height() override
  {
    return 0;
  }

  virtual int get_width() override
  {
    return 0;
  }

  virtual void set_location( std::unique_ptr<WorldCoordinates> new_location ) override
  {
  }

  virtual WorldCoordinates& get_location() const override
  {
    return *origin;
  }

  virtual void update_screen_position( ScreenWindow& window ) override
  {
    for( auto& render_component : get_render_components() )
      {
        std::unique_ptr<ScreenCoordinates> screen_location = window.project( 
          *render_component,
          get_location()
          );

        render_component -> set_screen_location(
          move( screen_location )
          );
      }
  }

  virtual void accept_renderer( GameRenderer& renderer ) override
  {
  }

protected:

    std::function<void()> update_delegate;

private:

  std::unique_ptr<WorldCoordinates> origin;

};

#endif
