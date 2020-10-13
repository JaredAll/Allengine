#include "world_coordinates.h"
#include <memory>
#include <ostream>

using std::make_unique;
using std::unique_ptr;
using std::ostream;

WorldCoordinates::WorldCoordinates( int x_param, int y_param )
  : x( x_param ), y( y_param )
{}

int WorldCoordinates::get_world_x() const
{
  return x;
}

void WorldCoordinates::set_world_x( int param_x )
{
  x = param_x;
}

int WorldCoordinates::get_world_y() const
{
  return y;
}

void WorldCoordinates::set_world_y( int param_y )
{
  y = param_y;
}

unique_ptr<WorldCoordinates> WorldCoordinates::operator+( WorldCoordinates const& other) const
{
  return make_unique<WorldCoordinates>(
    x + other.get_world_x(),
    y + other.get_world_y()
    );
}

ostream& operator<<( ostream& os, const WorldCoordinates& coordinates )
{
  os << "world x: " << coordinates.x << " world y: " << coordinates.y;
  return os;
}
