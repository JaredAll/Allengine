#include "screen_coordinates.h"
#include <memory>

using std::make_unique;

ScreenCoordinates::ScreenCoordinates( int x, int y )
{
  location = make_unique<Point>( x, y );
}

Point& ScreenCoordinates::get_location()
{
  return *location;
}
