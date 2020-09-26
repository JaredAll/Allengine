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

unique_ptr<ScreenCoordinates> ScreenWindow::project( WorldCoordinates& coordinates )
{
  int upper_left_x = upper_left_corner -> get_location().get_x();
  int lower_right_x = lower_right_corner -> get_location().get_x();
  int input_x = coordinates.get_location().get_x();

  int input_screen_projection_x = input_x - ( ( upper_left_x + lower_right_x ) / 2 );

  int upper_left_y = upper_left_corner -> get_location().get_y();
  int lower_right_y = lower_right_corner -> get_location().get_y();
  int input_y = coordinates.get_location().get_y();

  int input_screen_projection_y = input_y - ( ( upper_left_y + lower_right_y ) / 2 );

  return make_unique<ScreenCoordinates>(
    input_screen_projection_x,
    input_screen_projection_y );
}
