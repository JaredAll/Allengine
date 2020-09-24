#include "point.h"

Point::Point( int param_x, int param_y )
  : x( param_x ), y( param_y )
{
}

Point::~Point()
{
}

int Point::get_x() const
{
  return x;
}

void Point::set_x( int param_x )
{
  x = param_x;
}

void Point::set_y( int param_y )
{
  y = param_y;
}

int Point::get_y() const
{
  return y;
}
