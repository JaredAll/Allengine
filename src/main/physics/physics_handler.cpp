#include "physics_handler.h"
#include "game_component.h"

using std::make_unique;

bool PhysicsHandler::detectCollision( GameComponent& first, GameComponent& second )
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
