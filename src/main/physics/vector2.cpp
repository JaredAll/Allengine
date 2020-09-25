#include "vector2.h"
#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;

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

unique_ptr<Vector2> Vector2::add( Vector2& vector )
{
  float new_x_component = this -> get_x_component() + vector.get_x_component();
  float new_y_component = this -> get_y_component() + vector.get_y_component();

  float new_magnitude = sqrt( pow( new_x_component, 2 ) + pow( new_y_component, 2 ) );
  float new_theta = atan( new_y_component / new_x_component );

  std::cout << "new_magnitude: " << new_magnitude << std::endl;
  std::cout << "new_theta: " << new_theta << std::endl;

  return move( std::make_unique<Vector2>( new_magnitude, new_theta ) );
}
