#ifndef JAREDALL_SCREEN_WINDOW
#define JAREDALL_SCREEN_WINDOW

#include "world_coordinates.h"
#include "screen_coordinates.h"
#include <memory>
#include "test_component.h"

class ScreenWindow : public TestComponent
{
public:

  ScreenWindow( std::unique_ptr<WorldCoordinates> upper_left_corner,
                std::unique_ptr<WorldCoordinates> lower_right_corner );

  std::unique_ptr<ScreenCoordinates> project( WorldCoordinates const& coordinates );

  void scroll_x( int displacement );

  void update();

  void update( InputEvent& event );

  bool accepting_input();

  std::vector<std::unique_ptr<Sprite>>& get_render_components();

private:

  std::unique_ptr<WorldCoordinates> upper_left_corner;
  std::unique_ptr<WorldCoordinates> lower_right_corner;
  std::vector<std::unique_ptr<Sprite>> render_components;
  
};

#endif
