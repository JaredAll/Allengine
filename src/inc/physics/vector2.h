#ifndef JAREDALL_ALLENGINE_VECTOR2
#define JAREDALL_ALLENGINE_VECTOR2

#include <memory>
#include <cmath>
#include <iostream>
#include <utility>
#include "vector_qualities.h"

#define EPSILON 0.0001


template<typename Quality>
class Vector2
{
public:

  Vector2( float param_magnitude, float param_theta )
    : magnitude( param_magnitude )
  {
    theta = param_theta < 0 ? param_theta + 2 * M_PI : param_theta;
    quality = Quality{};
  }

  Vector2( Vector2<Quality> const& other )
  {
    theta = other.get_theta() < 0 ? other.get_theta() + 2 * M_PI : other.get_theta();
    magnitude = other.get_magnitude();
    quality = Quality{};
  }

  float get_x_component() const
  {
    return magnitude * cos( theta );
  }

  float get_y_component() const
  {
    return magnitude * sin( theta );
  }

  float get_magnitude() const
  {
    return magnitude;
  }

  float get_theta() const
  {
    return theta;
  }

  Quality get_quality() const
  {
    return quality;
  }

  std::unique_ptr<Vector2<Quality>> operator+( Vector2<Quality> const& vector ) const
  {
    float new_x_component = this -> get_x_component() + vector.get_x_component();
    float new_y_component = this -> get_y_component() + vector.get_y_component();

    float new_magnitude = sqrt( pow( new_x_component, 2 ) + pow( new_y_component, 2 ) );
    float new_theta = std::atan2( new_y_component, new_x_component );

    return move( std::make_unique<Vector2>( new_magnitude, new_theta ) );
  }

  bool operator==( Vector2<Quality> const& other )
  {
    return ( std::abs( magnitude - other.get_magnitude() ) < EPSILON )
      && ( std::abs( theta - other.get_theta() ) < EPSILON );
  }

private:

  float magnitude;
  float theta;
  Quality quality;

};


#endif
