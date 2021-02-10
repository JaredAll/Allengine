#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "physics_component.h"
#include "render_component.h"
#include <vector>
#include <iostream>
#include "input_event.h"
#include "screen_coordinates.h"
#include "screen_window.h"

class GameRenderer;

class GameComponent
{
public:

  virtual void update() = 0;

  virtual void update( InputEvent& event ) = 0;

  virtual bool accepting_input() = 0;

  virtual int get_height() = 0;

  virtual int get_width() = 0;

  virtual ~GameComponent() = default;

  virtual void on_update( std::function<void()> on_update ) = 0;

  virtual void set_location( std::unique_ptr<WorldCoordinates> new_location ) = 0;

  virtual WorldCoordinates& get_location() const = 0;

  virtual void update_screen_position( ScreenWindow& window ) = 0;

  virtual void accept_renderer( GameRenderer& renderer ) = 0;

protected:

  GameComponent()
  {
  }
  
};

#endif
