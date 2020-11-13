#include "physics_handler.h"
#include "game_component.h"
#include "physics_component.h"
#include "world_coordinates.h"
#include <cmath>

using std::make_unique;
using std::unique_ptr;
using std::vector;

bool PhysicsHandler::detect_collision( PhysicsBall& first, PhysicsBall& second )
{
  WorldCoordinates first_upper_left = first.get_location();  
  WorldCoordinates first_lower_right = WorldCoordinates(
    first_upper_left.get_world_x() + first.get_width(),
    first_upper_left.get_world_y() + first.get_height()
    );

  WorldCoordinates second_upper_left = second.get_location();  
  WorldCoordinates second_lower_right = WorldCoordinates(
    second_upper_left.get_world_x() + second.get_width(),
    second_upper_left.get_world_y() + second.get_height()
    );

  return
    ( first_lower_right.get_world_x() >= second_upper_left.get_world_x() ) &&
    ( first_lower_right.get_world_x() <=
      ( second_lower_right.get_world_x() + first.get_width() ) ) &&
    
    ( ( first_upper_left.get_world_y() + first.get_height() ) >=
      second_upper_left.get_world_y() ) &&
    ( first_upper_left.get_world_y() <= second_lower_right.get_world_y() );
}

void PhysicsHandler::handle_collision( PhysicsBall& first, PhysicsBall& second )
{
  if( detect_collision( first, second ) )
  {    
    PhysicsComponent& first_physics = first.get_physics_component();
    PhysicsComponent& second_physics = second.get_physics_component();

    if( first_physics.is_inertial() )
    {
      handle_collision_inertial( first, second );
    }
    else
    {
      handle_collision_inertial( second, first );
    }
  }
}

void PhysicsHandler::handle_collisions( vector<unique_ptr<PhysicsBall>>& components )
{
  for( size_t i = 0; i < components.size() - 1; i++ )
  {
    for( size_t j = i + 1; j < components.size(); j++ )
    {
      handle_collision( *components.at( i ), *components.at( j ) );
    }
  }
}

void PhysicsHandler::handle_collision_inertial( PhysicsBall& inertial, PhysicsBall& in_motion )
{
  Vector2<Velocity>& old_velocity = in_motion.get_physics_component().get_velocity();
  float new_speed = old_velocity.get_magnitude() * .66;

  if( abs( new_speed ) < 1 )
  {
    int new_motion_x_collision = in_motion.get_location().get_world_x();
    int new_motion_y_collision = inertial.get_location().get_world_y() - in_motion.get_height();

    unique_ptr<WorldCoordinates> new_collision_coordinates = make_unique<WorldCoordinates>(
      new_motion_x_collision,
      new_motion_y_collision );

    in_motion.set_location( move( new_collision_coordinates ) );

    in_motion.get_physics_component().freeze();
  }
  else
  {
    int new_motion_x_no_collision = in_motion.get_location().get_world_x();
    int new_motion_y_no_collision = inertial.get_location().get_world_y() -
      2 * in_motion.get_height();

    unique_ptr<WorldCoordinates> new_motion_coordinates = make_unique<WorldCoordinates>(
      new_motion_x_no_collision,
      new_motion_y_no_collision );

    in_motion.set_location( move( new_motion_coordinates ) );

    in_motion.get_physics_component().set_velocity(
      make_unique<Vector2<Velocity>>( new_speed, 3 * M_PI_2 )
      );  
  }
}
