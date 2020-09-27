#include "physics_ball.h"
#include "game_component.h"
#include <memory>

using std::move;
using std::make_unique;
using std::unique_ptr;
using std::vector;

PhysicsBall::PhysicsBall( unique_ptr<WorldCoordinates> location_param,
                          unique_ptr<Sprite> ball_sprite_param ) : GameComponent()
{
  set_location( move( location_param ) );
  render_components.push_back( move ( ball_sprite_param ) );
}

void PhysicsBall::update()
{
  int new_location_x = get_location().get_world_x() + 10;
  int new_location_y = get_location().get_world_y() + 10;

  set_location(
    make_unique<WorldCoordinates>(
      new_location_x,
      new_location_y )
    );
}

void PhysicsBall::update( InputEvent& event )
{  
}

bool PhysicsBall::accepting_input()
{
  return false;
}

vector<unique_ptr<Sprite>>& PhysicsBall::get_render_components()
{
  return render_components;
}
