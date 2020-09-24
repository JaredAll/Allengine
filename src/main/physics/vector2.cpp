#include "vector2.h"
#include <cmath>

Vector2::Vector2( float param_magnitude, float param_theta )
  : magnitude( param_magnitude ), theta( param_theta )
{
}

float Vector2::get_x_component()
{
  return magnitude * cos( theta );
}

float Vector2::get_y_component()
{
  return magnitude * sin( theta );
}
