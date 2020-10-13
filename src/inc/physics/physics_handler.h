#ifndef JAREDALL_ALLENGINE_PHYSICS_HANDLER
#define JAREDALL_ALLENGINE_PHYSICS_HANDLER

#include "game_component.h"
#include "physics_component.h"
class PhysicsHandler
{
public:

  bool detect_collision( GameComponent& first, GameComponent& second );

  void handle_collision( GameComponent& first, GameComponent& second );

private:

  void handle_collision_inertial( GameComponent& inertial, GameComponent& in_motion );
  
};

#endif
