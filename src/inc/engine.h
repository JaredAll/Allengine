#include "cleanup.h"
#include "game_component.h"
#include "input_event.h"
#include "input_handler.h"
#include "render_component.h"
#include "game_renderer.h"
#include <SDL.h>
#include <memory>

#ifndef JAREDALL_TETRIS_ENGINE
#define JAREDALL_TETRIS_ENGINE

class Engine
{
public:

  ~Engine();

  void initialize( int height, int width );

  template< typename T, typename = typename std::enable_if_t<
                          std::is_base_of<GameComponent, T>::value>>
  void advance( std::vector<std::unique_ptr<T>>& components )
  {
    if( should_render )
    {
      window -> scroll_x( current_scroll );
      render_components( components );
    }

    InputEvent& event = process_input();

    update_components( event, components );
  }

  void quit();

  bool peek_has_updated();

  GameRenderer& get_renderer();

  void set_screen_window( std::unique_ptr<ScreenWindow> param_window );

  void set_current_scroll( int param_current_scroll );

private:

  template< typename T >
  void render_components( std::vector<std::unique_ptr<T>>& components )
  {
    for( auto& component : components )
    {
      component -> update_screen_position( *window );
    }

    renderer -> render( components );
  
    frame_count++;
    should_render = false;
    should_update = true;
  }

  template< typename T >
  void update_components( InputEvent& input_event,
                          std::vector<std::unique_ptr<T>>& components )
  {
    for( auto& component : components )
    {
      if( should_update )
      {
        component -> update();
      }
      if( component -> accepting_input() )
      {
        component -> update( input_event );
      }
      has_updated = true;
    }
    should_update = false;
  }

  InputEvent& process_input();

  void maintain_time();

  std::unique_ptr<InputHandler> input_handler;
  std::unique_ptr<GameRenderer> renderer;
  std::unique_ptr<ScreenWindow> window;
  int current_scroll;
  bool should_render;
  bool should_update;
  bool has_updated;
  bool running;
  int frame_count;
};

#endif
