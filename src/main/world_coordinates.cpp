#include "world_coordinates.h"
#include <memory>

using std::make_unique;

WorldCoordinates::WorldCoordinates( int x, int y )
{
  location = make_unique<Point>( x, y );
}

Point& WorldCoordinates::get_location()
{
  return *location;
}
