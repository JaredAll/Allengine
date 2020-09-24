#include "engine.h"
#include "SDL_events.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "cleanup.h"
#include "input_type.h"
#include "render_component.h"
#include <iostream>
#include <future>
#include <memory>
#include "sprite_config.h"

using std::unique_ptr;
using std::make_unique;
using std::thread;
using std::vector;

Engine::~Engine()
{
  running = false;
  SDL_VideoQuit();
  SDL_Quit();
}

void Engine::initialize( int height, int width )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "SDL_Init failed" << std::endl;
  }

  unique_ptr<SDL_Window, SDL_Window_Destroyer> win {
    SDL_CreateWindow("Tetris",
                     SDL_WINDOWPOS_CENTERED,
                     SDL_WINDOWPOS_CENTERED,
                     width,
                     height,
                     SDL_WINDOW_SHOWN)
      };

  if (!win)
  {
    std::cout << "Create Window failed" << std::endl;
    SDL_Quit();
  }
  else
  {
    input_handler = make_unique<InputHandler>();
    renderer = make_unique<GameRenderer>( move( win ) );
    thread timer{ [=](){ maintain_time(); } };
    timer.detach();
    should_render = true;
    should_update = true;
    frame_count = 0;
    running = true;
  }
}

void Engine::quit()
{
  exit( 0 );
}

InputEvent& Engine::process_input()
{
  InputEvent& event = input_handler -> handle_input();
  if( event.escape() )
  {
    quit();
  }
  return event;
}

GameRenderer& Engine::get_renderer()
{
  return *renderer;
}

bool Engine::peek_has_updated()
{
  bool peek_update = false;
  if( has_updated )
  {
    has_updated = false;
    peek_update = true;
  }
  return peek_update;
}

void Engine::maintain_time()
{
  Uint32 ms_per_frame = 16;
  Uint32 last_frame = SDL_GetTicks();
  while( running )
  {
    Uint32 current_time = SDL_GetTicks();
    if( current_time - last_frame >= ms_per_frame )
    {
      should_render = true;
      last_frame = current_time;
    }
  }
}
