#ifndef JAREDALL_ALLENGINE_PHYSICS_HANDLER
#define JAREDALL_ALLENGINE_PHYSICS_HANDLER

#include "game_component.h"
#include "physics_ball.h"
#include "physics_component.h"

class PhysicsHandler
{
public:

  bool detect_collision( PhysicsBall& first, PhysicsBall& second );

  void handle_collision( PhysicsBall& first, PhysicsBall& second );

private:

  void handle_collision_inertial( PhysicsBall& inertial, PhysicsBall& in_motion );
  
};

#endif
