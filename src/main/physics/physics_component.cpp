#include "physics_component.h"
#include "vector_qualities.h"
#include <memory>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using Force_v = Vector2<Force>;
using Acceleration_v = Vector2<Acceleration>;
using Velocity_v = Vector2<Velocity>;
using Displacement_v = Vector2<Displacement>;

PhysicsComponent::PhysicsComponent( float param_mass )
  : mass( param_mass )
{
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
  unique_ptr<Displacement_v> acceleration_displacement = acceleration -> integrate( delta_t, 2 );

  unique_ptr<Displacement_v> displacement = *velocity_displacement + *acceleration_displacement;

  velocity = make_unique<Velocity_v>( displacement -> get_magnitude() / delta_t,
                                      displacement -> get_theta() );

  return move( displacement );
}
