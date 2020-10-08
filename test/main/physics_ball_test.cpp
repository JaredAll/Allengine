#include "catch.hpp"
#include "physics_ball.h"
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

void shift_ball_x_y( PhysicsBall& ball_handle, float x, float y )
{
  int new_location_x = ball_handle.get_location().get_world_x() + x;
  int new_location_y = ball_handle.get_location().get_world_y() + y;

  ball_handle.set_location(
    make_unique<WorldCoordinates>(
      new_location_x,
      new_location_y )
    );
}

void run_while_visible(
  vector<unique_ptr<TestComponent>>& game_components,
  ScreenWindow& window,
  unique_ptr<Engine>& engine)
{
  bool visible = true;
  while( visible )
  {
    for( auto& component : game_components )
    {
      for( auto& render_component : component -> get_render_components() )
      {
        unique_ptr<ScreenCoordinates> screen_location = window.project( 
          *( render_component -> get_world_offset() +
             component -> get_location() )
          );

        visible = screen_location -> is_visible();

        render_component -> set_screen_location(
          move( screen_location )
          );
      }
    }
    engine -> advance( game_components );        
  }
}

TEST_CASE( "world to screen projection successful" )
{
  int width = 500;
  int height = 500;

  std::unique_ptr<Engine> engine = std::make_unique<Engine>();
  engine -> initialize( width, height );

  GameRenderer& renderer = engine -> get_renderer();

  unique_ptr<Sprite> ball_sprite = make_unique<Sprite>(
    make_unique<WorldCoordinates>( 0, 0 ),
    10,
    10,
    renderer.create_texture( "/home/jared/Games/Tetris/resources/j.png" )
    );

  unique_ptr<PhysicsBall> ball = make_unique<PhysicsBall>(
    make_unique<WorldCoordinates>( 0, 0 ),
    move( ball_sprite )
    );

  PhysicsBall& ball_handle = *ball;

  vector<unique_ptr<TestComponent>> game_components;
  game_components.push_back( move( ball ) );

  unique_ptr<WorldCoordinates> upper_left_corner = make_unique<WorldCoordinates>( 0, 0 );
  unique_ptr<WorldCoordinates> lower_right_corner = make_unique<WorldCoordinates>( width, height );

  unique_ptr<ScreenWindow> screen_window = make_unique<ScreenWindow>(
    move( upper_left_corner ),
    move( lower_right_corner )
    );

  ScreenWindow& window = *screen_window;
  game_components.push_back( move( screen_window ) );

  // SECTION( "physics ball moves in world" )
  // {
  //   ball_handle.on_update( [&]{ shift_ball_x_y( ball_handle, 10, 10 ); } );

  //   run_while_visible( game_components, window, engine );
    
  //   REQUIRE( game_components.at( 0 ) -> get_location().get_world_x() == 510 );
  //   REQUIRE( game_components.at( 0 ) -> get_location().get_world_y() == 510 );
  // }

  // SECTION( "physics ball and screen window both move" )
  // {
  //   ball_handle.on_update( [&]{ shift_ball_x_y( ball_handle, 10, 10 ); } );
  //   window.on_update( [&]{ window.scroll_x( 10 ); } );

  //   run_while_visible( game_components, window, engine );
        
  //   REQUIRE( game_components.at( 0 ) -> get_location().get_world_x() == 510 );
  //   REQUIRE( game_components.at( 0 ) -> get_location().get_world_y() == 510 );
  // }

  // SECTION( "screen window shifts left" )
  // {
  //   window.on_update( [&]{ window.scroll_x( -10 ); } );

  //   run_while_visible( game_components, window, engine );
    
  //   REQUIRE( game_components.at( 0 ) -> get_location().get_world_x() == 0 );
  //   REQUIRE( game_components.at( 0 ) -> get_location().get_world_y() == 0 );
  // }

  // SECTION( "screen window shifts left and first ball shift left, second ball stationary" )
  // {
  //   unique_ptr<Sprite> ball_sprite_2 = make_unique<Sprite>(
  //     make_unique<WorldCoordinates>( 0, 0 ),
  //     10,
  //     10,
  //     renderer.create_texture( "/home/jared/Games/Tetris/resources/j.png" )
  //     );

  //   unique_ptr<PhysicsBall> ball_2 = make_unique<PhysicsBall>(
  //     make_unique<WorldCoordinates>( 0, 100 ),
  //     move( ball_sprite_2 )
  //     );

  //   PhysicsBall& ball_2_handle = *ball_2;

  //   game_components.push_back( move( ball_2 ) );

  //   window.on_update( [&]{ window.scroll_x( 3 ); } );
  //   ball_handle.on_update( [&]{ shift_ball_x_y( ball_handle, 10, 1 ); } );
  //   ball_2_handle.on_update( [&]{ shift_ball_x_y( ball_2_handle, 8, 6 ); } );

  //   run_while_visible( game_components, window, engine );
  // }

  SECTION( "First physics component test" )
  {
    float ball_mass = 10;
    float time_elapsed = 0;

    unique_ptr<PhysicsComponent> physics_component = make_unique<PhysicsComponent>( ball_mass );
    unique_ptr<Vector2<Force>> gravity = make_unique<Vector2<Force>>( 10, 3 * M_PI_2 );

    physics_component -> consider( move( gravity ) );

    ball_handle.on_update( [&]
                           {
                             unique_ptr<Vector2<Displacement>> displacement =
                               physics_component -> advance( time_elapsed );
                             shift_ball_x_y(
                               ball_handle,
                               displacement -> get_x_component_magnitude(),
                               displacement -> get_y_component_magnitude()
                               );
                           }
      );

    run_while_visible( game_components, window, engine );    
  }
}
