#include "physics_ball.h"
#include "game_component.h"
#include "physics_component.h"
#include <cmath>
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
  controllable = false;
}

PhysicsBall::PhysicsBall( unique_ptr<WorldCoordinates> location_param,
                          unique_ptr<Sprite> ball_sprite_param ) : TestComponent()
{
  physics_component = make_unique<PhysicsComponent>( 1, false );
  set_location( move( location_param ) );
  render_components.push_back( move ( ball_sprite_param ) );
  controllable = false;
}

bool PhysicsBall::accepting_input()
{
  return controllable;
}

vector<unique_ptr<Sprite>>& PhysicsBall::get_render_components()
{
  return render_components;
}

int PhysicsBall::get_width()
{
  return render_components.at( 0 ) -> get_w();
}

int PhysicsBall::get_height()
{
  return render_components.at( 0 ) -> get_h();
}

void PhysicsBall::update()
{
  update_delegate();
}

void PhysicsBall::update( InputEvent& event )
{
  float speed = 1;
  float direction = 0;

  if( event.down_up() )
  {
    direction = M_PI_2;
  }
  else if( event.left_up() )
  {
    direction = M_PI;
    speed = 3;
  }
  else if( event.right_up() )
  {
    direction = 0;
    speed = 3;
  }
  else if( event.up_up() )
  {
    speed = 5;
    direction = 3 * M_PI_2;
  }

  if( event.down_up() || event.left_up() || event.right_up() || event.up_up() )
  {
    physics_component -> set_velocity( make_unique<Vector2<Velocity>>( speed, direction ) );  
  }
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

WorldCoordinates& PhysicsBall::get_location() const
{
  return physics_component -> get_location();
}

void PhysicsBall::mark_controllable()
{
  controllable = true;
}
