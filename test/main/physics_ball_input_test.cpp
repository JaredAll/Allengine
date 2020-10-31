#include "SDL_timer.h"
#include "catch.hpp"
#include "physics_ball.h"
#include "physics_handler.h"
#include "screen_window.h"
#include "sprite.h"
#include "test_component.h"
#include "world_coordinates.h"
#include "engine.h"
#include "physics_component.h"
#include <cmath>

using std::unique_ptr;
using std::make_unique;
using std::vector;

void run_while_no_collision(
  vector<unique_ptr<PhysicsBall>>& game_components,
  ScreenWindow& window,
  unique_ptr<Engine>& engine);

void run_for_duration(
  vector<unique_ptr<PhysicsBall>>& game_components,
  ScreenWindow& window,
  unique_ptr<Engine>& engine,
  int milliseconds )
{
  unique_ptr<PhysicsHandler> physics_handler = make_unique<PhysicsHandler>();

  Uint32 begin = SDL_GetTicks();
  Uint32 now = begin;
  while( now - begin < 8000 )
  {
    now = SDL_GetTicks();
    for( auto& component : game_components )
    {
      component -> update_screen_position( window );
    }
    engine -> advance( game_components );        
  }
}

TEST_CASE( "test physics ball input" )
{
  int width = 500;
  int height = 500;
  float delta_t = 2;

  std::unique_ptr<Engine> engine = std::make_unique<Engine>();
  engine -> initialize( width, height );

  GameRenderer& renderer = engine -> get_renderer();

  unique_ptr<Sprite> first_ball_sprite = make_unique<Sprite>(
    make_unique<WorldCoordinates>( 0, 0 ),
    10,
    10,
    renderer.create_texture( "/home/jared/Games/Tetris/resources/j.png" )
    );

  float ball_mass = 10;

  unique_ptr<PhysicsComponent> first_ball_physics_component =
    make_unique<PhysicsComponent>( ball_mass, false );

  PhysicsComponent& first_physics = *first_ball_physics_component;

  unique_ptr<PhysicsBall> first_ball = make_unique<PhysicsBall>(
    make_unique<WorldCoordinates>( 0, 0 ),
    move( first_ball_physics_component ),
    move( first_ball_sprite )
    );

  PhysicsBall& first_ball_handle = *first_ball;

  vector<unique_ptr<PhysicsBall>> game_components;
  game_components.push_back( move( first_ball ) );

  unique_ptr<WorldCoordinates> upper_left_corner = make_unique<WorldCoordinates>( 0, 0 );
  unique_ptr<WorldCoordinates> lower_right_corner = make_unique<WorldCoordinates>( width, height );

  unique_ptr<ScreenWindow> screen_window = make_unique<ScreenWindow>(
    move( upper_left_corner ),
    move( lower_right_corner )
    );

  ScreenWindow& window = *screen_window;

  engine -> set_screen_window( move( screen_window ) );
  engine -> set_current_scroll( 0 );

  SECTION( "First physics component collision test: input playground" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<Vector2<Force>> gravity = make_unique<Vector2<Force>>( 1, M_PI_2 );

    first_physics.consider( move( gravity ) );

    first_ball_handle.set_location( make_unique<WorldCoordinates>( height / 2, width / 2 ) );
    first_ball_handle.mark_controllable();

    first_ball_handle.on_update( [&] {
      first_physics.advance( delta_t );
    });

    run_for_duration( game_components, window, engine, 10000 );
  }

  SECTION( "First physics component collision test: ground bounce" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<Sprite> ground_sprite = make_unique<Sprite>(
      make_unique<WorldCoordinates>( 0, 0 ),
      500,
      500,
      renderer.create_texture( "/home/jared/Games/Tetris/resources/s.png" )
      );

    unique_ptr<PhysicsComponent> ground_physics_component =
      make_unique<PhysicsComponent>( ball_mass, true );

    unique_ptr<PhysicsBall> ground = make_unique<PhysicsBall>(
      make_unique<WorldCoordinates>( 0, 400 ),
      move( ground_physics_component ),
      move( ground_sprite )
      );

    game_components.push_back( move( ground ) );

    unique_ptr<Vector2<Force>> gravity = make_unique<Vector2<Force>>( 1, M_PI_2 );

    first_physics.consider( move( gravity ) );

    first_ball_handle.set_location( make_unique<WorldCoordinates>( height / 2, width / 2 ) );
    first_ball_handle.mark_controllable();

    first_ball_handle.on_update( [&] {
      first_physics.advance( delta_t );
    });

    run_while_no_collision( game_components, window, engine );
  }
}
