#include "physics_handler.h"
#include "game_component.h"
#include "physics_component.h"
#include "world_coordinates.h"

using std::make_unique;
using std::unique_ptr;

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
    ( first_lower_right.get_world_x() <= second_lower_right.get_world_x() ) &&
    ( first_upper_left.get_world_y() >= second_upper_left.get_world_y() ) &&
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

void PhysicsHandler::handle_collision_inertial( PhysicsBall& inertial, PhysicsBall& in_motion )
{
  int new_motion_x = in_motion.get_location().get_world_x();
  int new_motion_y = inertial.get_location().get_world_y() - in_motion.get_height();

  unique_ptr<WorldCoordinates> new_motion_coordinates = make_unique<WorldCoordinates>(
    new_motion_x,
    new_motion_y );

  in_motion.set_location( move( new_motion_coordinates ) );

  in_motion.get_physics_component().freeze();
}
