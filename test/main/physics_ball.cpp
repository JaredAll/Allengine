#include "physics_ball.h"
#include "game_component.h"
#include <memory>

using std::move;
using std::make_unique;
using std::unique_ptr;
using std::vector;

PhysicsBall::PhysicsBall( unique_ptr<WorldCoordinates> location_param,
                          unique_ptr<Sprite> ball_sprite_param ) : TestComponent()
{
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
