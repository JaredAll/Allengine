#include "vector2.h"
#include <cmath>
#include <iostream>
#include <memory>

#define EPSILON 0.0001

using std::unique_ptr;

Vector2::Vector2( float param_magnitude, float param_theta )
  : magnitude( param_magnitude )
{
  theta = param_theta < 0 ? param_theta + 2 * M_PI : param_theta;
}

float Vector2::get_x_component() const
{
  return magnitude * cos( theta );
}

float Vector2::get_y_component() const
{
  return magnitude * sin( theta );
}

float Vector2::get_magnitude() const
{
  return magnitude;
}

float Vector2::get_theta() const
{
  return theta;
}

unique_ptr<Vector2> Vector2::add( Vector2 const& vector )
{
  float new_x_component = this -> get_x_component() + vector.get_x_component();
  float new_y_component = this -> get_y_component() + vector.get_y_component();

  float new_magnitude = sqrt( pow( new_x_component, 2 ) + pow( new_y_component, 2 ) );
  float new_theta = std::atan2( new_y_component, new_x_component );

  return move( std::make_unique<Vector2>( new_magnitude, new_theta ) );
}
