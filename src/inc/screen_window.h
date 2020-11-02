#ifndef JAREDALL_SCREEN_WINDOW
#define JAREDALL_SCREEN_WINDOW

#include "input_event.h"
#include "render_component.h"
#include "sprite.h"
#include "world_coordinates.h"
#include "screen_coordinates.h"
#include <functional>
#include <memory>

class GameComponent;

class ScreenWindow
{
public:

  ScreenWindow( std::unique_ptr<WorldCoordinates> upper_left_corner,
                std::unique_ptr<WorldCoordinates> lower_right_corner );

  std::unique_ptr<ScreenCoordinates> project( RenderComponent const&, WorldCoordinates const& );

  void scroll_x( int displacement );

  void focus( GameComponent& component );

private:

  std::unique_ptr<WorldCoordinates> upper_left_corner;
  std::unique_ptr<WorldCoordinates> lower_right_corner;
  std::vector<std::unique_ptr<Sprite>> render_components;
  
};

#endif
