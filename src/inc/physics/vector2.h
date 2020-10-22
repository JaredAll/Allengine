#ifndef JAREDALL_ALLENGINE_VECTOR2
#define JAREDALL_ALLENGINE_VECTOR2

#include <memory>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <utility>
#include "vector_qualities.h"
#include <functional>

#define EPSILON 0.0001

template<typename Quality>
class Vector2Base
{
public:
  
  Vector2Base( float param_magnitude, float param_theta )
    : magnitude( param_magnitude )
  {
    theta = param_theta < 0 ? param_theta + 2 * M_PI : param_theta;
    parametric_update = []( float delta_t ){};
    quality = Quality{};
  }

  Vector2Base( Vector2Base<Quality> const& other )
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
    return std::make_unique<Vector2Base<Quality>>( get_x_component_magnitude(), 0 );
  }

  auto get_y_component() const
  {
    return std::make_unique<Vector2Base<Quality>>( get_y_component_magnitude(), M_PI_2 );
  }

  float get_magnitude() const
  {
    return magnitude;
  }

  void set_magnitude( float param_magnitude )
  {
    magnitude = param_magnitude;
  }

  float get_theta() const
  {
    return theta;
  }

  void set_theta( float param_theta )
  {
    theta = param_theta;
  }

  Quality get_quality() const
  {
    return quality;
  }

  void set_parametric_update( std::function<void( float )> update_function )
  {
    parametric_update = update_function;
  }

  void update( float delta_t )
  {
    parametric_update( delta_t );
  }

  std::unique_ptr<Vector2Base<Quality>> operator+( Vector2Base<Quality> const& vector ) const
  {
    float new_x_component = this ->
      get_x_component_magnitude() + vector.get_x_component_magnitude();
    
    float new_y_component = this ->
      get_y_component_magnitude() + vector.get_y_component_magnitude();

    float new_magnitude = sqrt( pow( new_x_component, 2 ) + pow( new_y_component, 2 ) );
    float new_theta = std::atan2( new_y_component, new_x_component );

    return move( std::make_unique<Vector2Base>( new_magnitude, new_theta ) );
  }

  bool operator==( Vector2Base<Quality> const& other )
  {
    return ( std::abs( magnitude - other.get_magnitude() ) < EPSILON )
      && ( std::abs( theta - other.get_theta() ) < EPSILON );
  }

private:

  float magnitude;
  float theta;
  Quality quality;
  std::function<void( float )> parametric_update;
  
};

template<typename Quality, typename = void>
class Vector2 : public Vector2Base<Quality>
{
public:

  Vector2( float magnitude, float theta ) : Vector2Base<Quality>( magnitude, theta )
  {
  }

  Vector2( Vector2<Quality> const& other )
    : Vector2Base<Quality>(
      other.get_theta() < 0 ? other.get_theta() + 2 * M_PI : other.get_theta(),
      other.get_magnitude() )
  {
  }

  std::unique_ptr<Vector2<Quality>> operator+( Vector2<Quality> const& vector ) const
  {
    std::unique_ptr<Vector2Base<Quality>> vector_base = (
      this -> Vector2Base<Quality>::operator+( vector ) );
    
    return std::make_unique<Vector2<Quality>>( vector_base -> get_magnitude(),
                                          vector_base -> get_theta() );
  }

};

template<typename Quality>
class Vector2<Quality,
              std::enable_if_t<IsIntegratableT<Quality>{} &&
              !IsTwiceIntegratableT<Quality>{}>> : public Vector2Base<Quality>
{
public:

  using Vector2Base<Quality>::operator+;

  Vector2( float magnitude, float theta ) : Vector2Base<Quality>( magnitude, theta )
  {
  }

  Vector2( Vector2<Quality> const& other )
    : Vector2Base<Quality>(
      other.get_theta() < 0 ? other.get_theta() + 2 * M_PI : other.get_theta(),
      other.get_magnitude() )
  {
  }

  std::unique_ptr<Vector2<Quality>> operator+( Vector2<Quality> const& vector ) const
  {
    std::unique_ptr<Vector2Base<Quality>> vector_base =
      ( this -> Vector2Base<Quality>::operator+( vector ) );
    
    return std::make_unique<Vector2<Quality>>( vector_base -> get_magnitude(),
                                          vector_base -> get_theta() );
  }

  auto integrate( float delta_t )
  {
    using Integration = typename Quality::Integration;

    std::unique_ptr<Vector2<Integration>> integrated_x_component =
      std::make_unique<Vector2<Integration>>(
        this -> get_x_component_magnitude() * ( delta_t ),
        0 );

    std::unique_ptr<Vector2<Integration>> integrated_y_component =
      std::make_unique<Vector2<Integration>>( 
        this -> get_y_component_magnitude() * ( delta_t ), 
        M_PI_2 );

    return move( 
      *integrated_x_component + *integrated_y_component
      );
  }
};

template<typename Quality>
class Vector2<Quality, std::enable_if_t<IsTwiceIntegratableT<Quality>{}>>
  : public Vector2Base<Quality>
{
public:

  using Vector2Base<Quality>::operator+;

  Vector2( float magnitude, float theta ) : Vector2Base<Quality>( magnitude, theta )
  {
  }

  Vector2( Vector2<Quality> const& other )
    : Vector2Base<Quality>(
      other.get_theta() < 0 ? other.get_theta() + 2 * M_PI : other.get_theta(),
      other.get_magnitude() )
  {
  }

  std::unique_ptr<Vector2<Quality>> operator+( Vector2<Quality> const& vector ) const
  {
    std::unique_ptr<Vector2Base<Quality>> vector_base =
      ( this -> Vector2Base<Quality>::operator+( vector ) );
    
    return std::make_unique<Vector2<Quality>>( vector_base -> get_magnitude(),
                                          vector_base -> get_theta() );
  }

  auto integrate( float delta_t )
  {
    using Integration = typename Quality::Integration;

    std::unique_ptr<Vector2<Integration>> integrated_x_component =
      std::make_unique<Vector2<Integration>>(
        this -> get_x_component_magnitude() * ( delta_t ),
        0 );

    std::unique_ptr<Vector2<Integration>> integrated_y_component =
      std::make_unique<Vector2<Integration>>( 
        this -> get_y_component_magnitude() * ( delta_t ), 
        M_PI_2 );

    return std::move(
      *integrated_x_component + *integrated_y_component
      );
  }

  auto integrate_2( float delta_t )
  {
    using Integration2 = typename Quality::Integration2;

    std::unique_ptr<Vector2<Integration2>> integrated_x_component =
      std::make_unique<Vector2<Integration2>>(
        this -> get_x_component_magnitude() * ( std::pow( delta_t, 2 ) / 2 ),
        0 );

    std::unique_ptr<Vector2<Integration2>> integrated_y_component =
      std::make_unique<Vector2<Integration2>>( 
        this -> get_y_component_magnitude() * ( std::pow( delta_t, 2 ) / 2 ), 
        M_PI_2 );

    return std::move(
      *integrated_x_component + *integrated_y_component
      );
  }
};


#endif
