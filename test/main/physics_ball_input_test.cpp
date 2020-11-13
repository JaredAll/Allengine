#include "SDL_timer.h"
#include "catch.hpp"
#include "physics_ball.h"
#include "physics_handler.h"
#include "screen_window.h"
#include "sprite.h"
#include "test_component.h"
#include "test_component_factory.h"
#include "world_coordinates.h"
#include "engine.h"
#include "physics_component.h"
#include <cmath>
#include <memory>

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
  while( now - begin < milliseconds )
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

    run_for_duration( game_components, window, engine, 0 );
  }

  SECTION( "First physics component collision test: platforms bounce" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<TestComponentFactory> component_factory = make_unique<TestComponentFactory>( renderer );
    
    PhysicsBallInput ground_1_input {
      500,
      500,
      "/home/jared/Games/Tetris/resources/s.png",
      0,
      450,
      ball_mass,
      true
    };

    game_components.push_back( component_factory -> build_physics_ball( ground_1_input ) );

    PhysicsBallInput ground_2_input {
      500,
      500,
      "/home/jared/Games/Tetris/resources/s.png",
      700,
      400,
      ball_mass,
      true
    };

    game_components.push_back( component_factory -> build_physics_ball( ground_2_input ) );

    PhysicsBallInput ground_3_input {
      500,
      500,
      "/home/jared/Games/Tetris/resources/s.png",
      -700,
      300,
      ball_mass,
      true
    };

    game_components.push_back( component_factory -> build_physics_ball( ground_3_input ) );    

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
