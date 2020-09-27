#include "screen_window.h"
#include "world_coordinates.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::move;

ScreenWindow::ScreenWindow( unique_ptr<WorldCoordinates> upper_left_corner_param,
                            unique_ptr<WorldCoordinates> lower_right_corner_param )
{
  upper_left_corner = move( upper_left_corner_param );
  lower_right_corner = move( lower_right_corner_param );
}

unique_ptr<ScreenCoordinates> ScreenWindow::project( WorldCoordinates const& coordinates )
{
  int upper_left_x = upper_left_corner -> get_world_x();
  int lower_right_x = lower_right_corner -> get_world_x();
  int input_x = coordinates.get_world_x();

  int upper_left_y = upper_left_corner -> get_world_y();
  int lower_right_y = lower_right_corner -> get_world_y();
  int input_y = coordinates.get_world_y();

  bool visible = input_x >= upper_left_x && input_x <= lower_right_x
    && input_y >= upper_left_y && input_y <= lower_right_y;

  int input_screen_projection_x = 0;
  int input_screen_projection_y = 0;

  if( visible )
  {
    input_screen_projection_x = input_x - upper_left_x;
    input_screen_projection_y = input_y - upper_left_y;
  }

  return make_unique<ScreenCoordinates>(
    input_screen_projection_x,
    input_screen_projection_y,
    visible );
}
