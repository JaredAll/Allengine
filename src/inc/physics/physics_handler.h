#ifndef JAREDALL_ALLENGINE_PHYSICS_HANDLER
#define JAREDALL_ALLENGINE_PHYSICS_HANDLER

#include "game_component.h"
class PhysicsHandler
{
public:

  bool detectCollision( GameComponent& first, GameComponent& second );
  
};

#endif
