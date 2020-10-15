#include "physics_ball.h"
#include "game_component.h"
#include "physics_component.h"
#include <memory>

using std::move;
using std::make_unique;
using std::unique_ptr;
using std::vector;

PhysicsBall::PhysicsBall( unique_ptr<WorldCoordinates> location_param,
                          unique_ptr<PhysicsComponent> physics_component_param,
                          unique_ptr<Sprite> ball_sprite_param ) : TestComponent()
{
  physics_component = move( physics_component_param );
  set_location( move( location_param ) );
  render_components.push_back( move ( ball_sprite_param ) );
}

PhysicsBall::PhysicsBall( unique_ptr<WorldCoordinates> location_param,
                          unique_ptr<Sprite> ball_sprite_param ) : TestComponent()
{
  physics_component = make_unique<PhysicsComponent>( 1, false );
  set_location( move( location_param ) );
  render_components.push_back( move ( ball_sprite_param ) );
}

bool PhysicsBall::accepting_input()
{
  return false;
}

vector<unique_ptr<Sprite>>& PhysicsBall::get_render_components()
{
  return render_components;
}

int PhysicsBall::get_height()
{
  return render_components.at( 0 ) -> get_h();
}

int PhysicsBall::get_width()
{
  return render_components.at( 0 ) -> get_w();
}

PhysicsComponent& PhysicsBall::get_physics_component()
{
  return *physics_component;
}

void PhysicsBall::set_physics_component( std::unique_ptr<PhysicsComponent> new_physics_component )
{
  physics_component = move( new_physics_component );
}

void PhysicsBall::set_location( std::unique_ptr<WorldCoordinates> new_location )
{
  physics_component -> set_location( move( new_location ) );
}

WorldCoordinates& PhysicsBall::get_location()
{
  return physics_component -> get_location();
}
