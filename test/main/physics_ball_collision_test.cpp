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

void shift_ball_x_y( PhysicsBall& ball_handle, float x, float y );

void run_while_no_collision(
  vector<unique_ptr<TestComponent>>& game_components,
  ScreenWindow& window,
  unique_ptr<Engine>& engine)
{
  unique_ptr<PhysicsHandler> physics_handler = make_unique<PhysicsHandler>();

  Uint32 begin = SDL_GetTicks();
  Uint32 now = begin;
  while( now - begin < 4000 )
  {
    now = SDL_GetTicks();

    physics_handler -> handle_collision(
        *game_components.at( 0 ),
        *game_components.at( 1 ) );
    
    for( auto& component : game_components )
    {
      for( auto& render_component : component -> get_render_components() )
      {
        unique_ptr<ScreenCoordinates> screen_location = window.project( 
          *( render_component -> get_world_offset() +
             component -> get_location() )
          );

        render_component -> set_screen_location(
          move( screen_location )
          );
      }
    }
    engine -> advance( game_components );        
  }
}

TEST_CASE( "test physics ball collision" )
{
  int width = 500;
  int height = 500;

  std::unique_ptr<Engine> engine = std::make_unique<Engine>();
  engine -> initialize( width, height );

  GameRenderer& renderer = engine -> get_renderer();

  unique_ptr<Sprite> first_ball_sprite = make_unique<Sprite>(
    make_unique<WorldCoordinates>( 0, 0 ),
    10,
    10,
    renderer.create_texture( "/home/jared/Games/Tetris/resources/j.png" )
    );

  unique_ptr<Sprite> second_ball_sprite = make_unique<Sprite>(
    make_unique<WorldCoordinates>( 0, 0 ),
    10,
    10,
    renderer.create_texture( "/home/jared/Games/Tetris/resources/j.png" )
    );

  unique_ptr<PhysicsBall> first_ball = make_unique<PhysicsBall>(
    make_unique<WorldCoordinates>( 0, 0 ),
    move( first_ball_sprite )
    );

  PhysicsBall& first_ball_handle = *first_ball;

  unique_ptr<PhysicsBall> second_ball = make_unique<PhysicsBall>(
    make_unique<WorldCoordinates>( 0, 300 ),
    move( second_ball_sprite )
    );

  PhysicsBall& second_ball_handle = *second_ball;

  vector<unique_ptr<TestComponent>> game_components;
  game_components.push_back( move( first_ball ) );
  game_components.push_back( move( second_ball ) );

  unique_ptr<WorldCoordinates> upper_left_corner = make_unique<WorldCoordinates>( 0, 0 );
  unique_ptr<WorldCoordinates> lower_right_corner = make_unique<WorldCoordinates>( width, height );

  unique_ptr<ScreenWindow> screen_window = make_unique<ScreenWindow>(
    move( upper_left_corner ),
    move( lower_right_corner )
    );

  ScreenWindow& window = *screen_window;
  game_components.push_back( move( screen_window ) );

  SECTION( "First physics component collision test: gravity" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<PhysicsComponent> first_ball_physics_component =
      make_unique<PhysicsComponent>( ball_mass, false );

    unique_ptr<PhysicsComponent> second_ball_physics_component =
      make_unique<PhysicsComponent>( ball_mass, true );

    PhysicsComponent& first_physics = *first_ball_physics_component;
    PhysicsComponent& second_physics = *second_ball_physics_component;

    unique_ptr<Vector2<Force>> gravity = make_unique<Vector2<Force>>( 1, M_PI_2 );
    first_ball_physics_component -> consider( move( gravity ) );

    first_ball_handle.set_physics_component( move( first_ball_physics_component ) );
    second_ball_handle.set_physics_component( move( second_ball_physics_component ) );

    first_ball_handle.on_update( [&]
                           {
                             time_elapsed += .01;
                             unique_ptr<Vector2<Displacement>> displacement =
                               first_physics.advance( time_elapsed );
                             shift_ball_x_y(
                               first_ball_handle,
                               displacement -> get_x_component_magnitude(),
                               displacement -> get_y_component_magnitude()
                               );
                           }
      );

    run_while_no_collision( game_components, window, engine );    
  }

  SECTION( "First physics component collision test: gravity with screen motion" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<PhysicsComponent> first_ball_physics_component =
      make_unique<PhysicsComponent>( ball_mass, false );

    unique_ptr<PhysicsComponent> second_ball_physics_component =
      make_unique<PhysicsComponent>( ball_mass, true );

    PhysicsComponent& first_physics = *first_ball_physics_component;
    PhysicsComponent& second_physics = *second_ball_physics_component;

    unique_ptr<Vector2<Force>> gravity = make_unique<Vector2<Force>>( 1, M_PI_2 );
    first_ball_physics_component -> consider( move( gravity ) );

    first_ball_handle.set_physics_component( move( first_ball_physics_component ) );
    second_ball_handle.set_physics_component( move( second_ball_physics_component ) );

    window.on_update( [&]{ window.scroll_x( -2 ); } );

    first_ball_handle.on_update( [&]
                           {
                             time_elapsed += .01;
                             unique_ptr<Vector2<Displacement>> displacement =
                               first_physics.advance( time_elapsed );
                             shift_ball_x_y(
                               first_ball_handle,
                               displacement -> get_x_component_magnitude(),
                               displacement -> get_y_component_magnitude()
                               );
                           }
      );

    run_while_no_collision( game_components, window, engine );    
  }

  SECTION( "First physics component collision test: gravity, blocks not aligned" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<PhysicsComponent> first_ball_physics_component =
      make_unique<PhysicsComponent>( ball_mass, false );

    unique_ptr<PhysicsComponent> second_ball_physics_component =
      make_unique<PhysicsComponent>( ball_mass, true );

    PhysicsComponent& first_physics = *first_ball_physics_component;
    PhysicsComponent& second_physics = *second_ball_physics_component;

    unique_ptr<Vector2<Force>> gravity = make_unique<Vector2<Force>>( 1, M_PI_2 );
    first_ball_physics_component -> consider( move( gravity ) );

    first_ball_handle.set_location( make_unique<WorldCoordinates>( 8, 0 ) );

    first_ball_handle.set_physics_component( move( first_ball_physics_component ) );
    second_ball_handle.set_physics_component( move( second_ball_physics_component ) );

    first_ball_handle.on_update( [&]
                           {
                             time_elapsed += .01;
                             unique_ptr<Vector2<Displacement>> displacement =
                               first_physics.advance( time_elapsed );
                             shift_ball_x_y(
                               first_ball_handle,
                               displacement -> get_x_component_magnitude(),
                               displacement -> get_y_component_magnitude()
                               );
                           }
      );

    run_while_no_collision( game_components, window, engine );    
  }
}
