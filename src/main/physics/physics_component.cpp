#include "physics_component.h"
#include "vector_qualities.h"
#include "world_coordinates.h"
#include <cmath>
#include <memory>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using Force_v = Vector2<Force>;
using Acceleration_v = Vector2<Acceleration>;
using Velocity_v = Vector2<Velocity>;
using Displacement_v = Vector2<Displacement>;

PhysicsComponent::PhysicsComponent( float param_mass, bool param_inertial )
  : mass( param_mass ), inertial( param_inertial )
{
  location = make_unique<WorldCoordinates>( 0, 0 );
  displacement = make_unique<Displacement_v>( 0, 0 );
  velocity = make_unique<Velocity_v>( 0, 0 );
}

void PhysicsComponent::consider( unique_ptr<Force_v> force )
{
  forces.push_back( move( force ) );
}

void PhysicsComponent::remove( unique_ptr<Force_v> force )
{
  vector<unique_ptr<Force_v>> new_forces;
  for( unique_ptr<Force_v>& current_force : forces )
  {
    if( !( (*current_force) == (*force) ) )
    {
      unique_ptr<Force_v> keep_force = make_unique<Force_v>( *current_force );
      new_forces.push_back( move( keep_force ) );
    }
  }
  
  forces = move( new_forces );
}

unique_ptr<Displacement_v> PhysicsComponent::advance( float delta_t )
{
  unique_ptr<Force_v> sum_forces = make_unique<Force_v>( 0, 0 );
  for( auto& current_force : forces )
  {
    sum_forces = move( *sum_forces + *current_force );
  }

  acceleration = make_unique<Acceleration_v>( sum_forces -> get_magnitude() / mass,
                                              sum_forces -> get_theta() );

  unique_ptr<Displacement_v> velocity_displacement = velocity -> integrate( delta_t, 1 );
  unique_ptr<Displacement_v> acceleration_displacement = acceleration -> integrate_2( delta_t );

  unique_ptr<Displacement_v> change_in_displacement =
    *velocity_displacement + *acceleration_displacement;

  unique_ptr<Displacement_v> new_displacement = *change_in_displacement + *displacement;

  velocity = make_unique<Velocity_v>( new_displacement -> get_magnitude() / delta_t,
                                      new_displacement -> get_theta() );

  displacement = make_unique<Displacement_v>( new_displacement -> get_magnitude(),
                                              new_displacement -> get_theta() );

  location = make_unique<WorldCoordinates>( displacement -> get_x_component_magnitude(),
                                            displacement -> get_y_component_magnitude() );

  for( auto& current_force : forces )
  {
    current_force -> update( delta_t );
  }

  return move( new_displacement );
}

bool PhysicsComponent::is_inertial()
{
  return inertial;
}

void PhysicsComponent::freeze()
{
  velocity -> set_magnitude( 0 );
  velocity -> set_theta( 0 );

  acceleration -> set_magnitude( 0 );
  acceleration -> set_theta( 0 );

  forces.clear();
}

void PhysicsComponent::set_location( unique_ptr<WorldCoordinates>& coordinates )
{
  float magnitude = std::sqrt(
    std::pow( coordinates -> get_world_x(), 2 ) +
    std::pow( coordinates -> get_world_y(), 2 ) );

  float theta = std::atan2( coordinates -> get_world_y(), coordinates -> get_world_x() );

  displacement = make_unique<Displacement_v>( magnitude, theta );
  
  location = make_unique<WorldCoordinates>( coordinates -> get_world_x(),
                                            coordinates -> get_world_y() );
}

WorldCoordinates& PhysicsComponent::get_location()
{
  return *location;
}
