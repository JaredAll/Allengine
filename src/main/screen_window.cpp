#include "screen_window.h"
#include "game_component.h"
#include "render_component.h"
#include "world_coordinates.h"
#include <memory>
#include <iostream>

using std::unique_ptr;
using std::make_unique;
using std::move;

ScreenWindow::ScreenWindow( unique_ptr<WorldCoordinates> upper_left_corner_param,
                            unique_ptr<WorldCoordinates> lower_right_corner_param )
{
  upper_left_corner = move( upper_left_corner_param );
  lower_right_corner = move( lower_right_corner_param );
}

unique_ptr<ScreenCoordinates> ScreenWindow::project( RenderComponent const& component,
                                                     WorldCoordinates const& location )
{
  unique_ptr<WorldCoordinates> coordinates = component.get_world_offset() + location;

  int upper_left_x = upper_left_corner -> get_world_x();
  int lower_right_x = lower_right_corner -> get_world_x();
  int input_x = coordinates -> get_world_x();

  int upper_left_y = upper_left_corner -> get_world_y();
  int lower_right_y = lower_right_corner -> get_world_y();
  int input_y = coordinates -> get_world_y();

  int top_right_x = input_x + component.get_w();

  bool visible =
    ( input_x >= upper_left_x && input_x <= lower_right_x
      && input_y >= upper_left_y && input_y <= lower_right_y ) ||
    ( top_right_x >= upper_left_x && top_right_x <= lower_right_x
      && input_y >= upper_left_y && input_y <= lower_right_y );

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

void ScreenWindow::scroll_x( int displacement )
{
  unique_ptr<WorldCoordinates> scroll_offset = make_unique<WorldCoordinates>( displacement, 0 );

  upper_left_corner = *upper_left_corner + *scroll_offset;
  lower_right_corner = *lower_right_corner + *scroll_offset;
}

void ScreenWindow::focus( GameComponent& component )
{
  int half_window_width = ( lower_right_corner -> get_world_x() -
                            upper_left_corner -> get_world_x() ) / 2;
  
  unique_ptr<WorldCoordinates> lower_right_shift = make_unique<WorldCoordinates>(
    component.get_location().get_world_x() + half_window_width,
    lower_right_corner -> get_world_y() );

  unique_ptr<WorldCoordinates> upper_left_shift = make_unique<WorldCoordinates>(
    component.get_location().get_world_x() - half_window_width,
    upper_left_corner -> get_world_y() );

  lower_right_corner = move( lower_right_shift );
  upper_left_corner = move( upper_left_shift );
}
