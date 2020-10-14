#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "physics_component.h"
#include "render_component.h"
#include <vector>
#include <iostream>
#include "input_event.h"

class GameComponent
{
public:

  virtual void update() = 0;

  virtual void update( InputEvent& event ) = 0;

  virtual bool accepting_input() = 0;

  virtual int get_height() = 0;

  virtual int get_width() = 0;

  virtual ~GameComponent() = default;

  void set_location( std::unique_ptr<WorldCoordinates> location_param )
  {
    physics_component -> set_location( location_param );
  }

  WorldCoordinates& get_location() const
  {
    return physics_component -> get_location();
  }

  void set_physics_component( std::unique_ptr<PhysicsComponent> physics )
  {
    physics_component = move( physics );
  }

  PhysicsComponent& get_physics_component() const
  {
    return *physics_component;
  }

protected:

  GameComponent(){}

private:

  std::unique_ptr<PhysicsComponent> physics_component;
  
};

#endif
