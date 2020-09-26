#include "screen_coordinates.h"
#include <memory>

using std::make_unique;

ScreenCoordinates::ScreenCoordinates( int x, int y, bool visible_param )
  : visible( visible_param )
{
  location = make_unique<Point>( x, y );
}

Point& ScreenCoordinates::get_location()
{
  return *location;
}

bool ScreenCoordinates::is_visible() const
{
  return visible;
}
