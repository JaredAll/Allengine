#include "catch.hpp"
#include "physics_ball.h"
#include "screen_window.h"
#include "sprite.h"
#include "world_coordinates.h"
#include "engine.h"

using std::unique_ptr;
using std::make_unique;
using std::vector;

TEST_CASE( "world to screen projection successful" )
{
  int width = 500;
  int height = 500;

  unique_ptr<WorldCoordinates> upper_left_corner = make_unique<WorldCoordinates>( 0, 0 );
  unique_ptr<WorldCoordinates> lower_right_corner = make_unique<WorldCoordinates>( width, height );

  unique_ptr<ScreenWindow> screen_window = make_unique<ScreenWindow>(
    move( upper_left_corner ),
    move( lower_right_corner )
    );

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

  vector<unique_ptr<PhysicsBall>> game_components;
  game_components.push_back( move( ball ) );

  while( true )
  {
    for( auto& component : game_components )
    {
      for( auto& render_component : component -> get_render_components() )
      {
        std::cout << component -> get_location() << std::endl;

        unique_ptr<ScreenCoordinates> screen_location = screen_window -> project( 
            *( render_component -> get_world_offset() +
               component -> get_location() )
          );

        std::cout << *screen_location << std::endl;
        std::cout << std::endl;

        render_component -> set_screen_location(
          move( screen_location )
          );
      }
    }
    engine -> advance( game_components );
  }
}
