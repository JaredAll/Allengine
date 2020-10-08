#ifndef JAREDALL_ALLENGINE_VECTOR2
#define JAREDALL_ALLENGINE_VECTOR2

#include <memory>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <utility>
#include "vector_qualities.h"

#define EPSILON 0.0001

template<typename Quality, typename = void>
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

  float get_x_component_magnitude() const
  {
    return magnitude * cos( theta );
  }

  float get_y_component_magnitude() const
  {
    return magnitude * sin( theta );
  }

  auto get_x_component() const
  {
    return std::make_unique<Vector2<Quality>>( get_x_component_magnitude(), 0 );
  }

  auto get_y_component() const
  {
    return std::make_unique<Vector2<Quality>>( get_y_component_magnitude(), M_PI_2 );
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
    float new_x_component = this ->
      get_x_component_magnitude() + vector.get_x_component_magnitude();
    
    float new_y_component = this ->
      get_y_component_magnitude() + vector.get_y_component_magnitude();

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

template<typename Quality>
class Vector2<Quality, std::enable_if_t<IsIntegratableT<Quality>{}>>
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

  float get_x_component_magnitude() const
  {
    return magnitude * cos( theta );
  }

  float get_y_component_magnitude() const
  {
    return magnitude * sin( theta );
  }

  auto get_x_component() const
  {
    return std::make_unique<Vector2<Quality>>( get_x_component_magnitude(), 0 );
  }

  auto get_y_component() const
  {
    return std::make_unique<Vector2<Quality>>( get_y_component_magnitude(), M_PI_2 );
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
    float new_x_component = this ->
      get_x_component_magnitude() + vector.get_x_component_magnitude();
    
    float new_y_component = this ->
      get_y_component_magnitude() + vector.get_y_component_magnitude();

    float new_magnitude = sqrt( pow( new_x_component, 2 ) + pow( new_y_component, 2 ) );
    float new_theta = std::atan2( new_y_component, new_x_component );

    return move( std::make_unique<Vector2<Quality>>( new_magnitude, new_theta ) );
  }

  std::unique_ptr<Vector2<Quality>> operator*( float scalar ) const
  {
    return move( std::make_unique<Vector2<Quality>>( magnitude * scalar, theta ) );
  }

  bool operator==( Vector2<Quality> const& other )
  {
    return ( std::abs( magnitude - other.get_magnitude() ) < EPSILON )
      && ( std::abs( theta - other.get_theta() ) < EPSILON );
  }

  auto integrate( float delta_t, int divisor )
  {
    using Integration = typename Quality::Integration;

    std::unique_ptr<Vector2<Integration>> integrated_x_component =
      std::make_unique<Vector2<Integration>>(
        get_x_component_magnitude() * ( delta_t / divisor ),
        0 );

    std::unique_ptr<Vector2<Integration>> integrated_y_component =
      std::make_unique<Vector2<Integration>>( 
        get_y_component_magnitude() * ( delta_t / divisor ), 
        M_PI_2 );

    return move(
      *integrated_x_component + *integrated_y_component
      );
  }

private:

  float magnitude;
  float theta;
  Quality quality;

};

#endif
