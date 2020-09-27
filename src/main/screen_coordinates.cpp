#include "screen_coordinates.h"
#include <memory>
#include <ostream>

using std::make_unique;
using std::ostream;

ScreenCoordinates::ScreenCoordinates( int x_param, int y_param, bool visible_param )
  : x( x_param ), y( y_param ), visible( visible_param )
{}

int ScreenCoordinates::get_screen_x() const
{
  return x;
}

int ScreenCoordinates::get_screen_y() const
{
  return y;
}

bool ScreenCoordinates::is_visible() const
{
  return visible;
}

ostream& operator<<( ostream& os, const ScreenCoordinates& coordinates )
{
  os << "screen x: " << coordinates.x << " screen y: " << coordinates.y << " visible: "
     << coordinates.visible;
  return os;
}
