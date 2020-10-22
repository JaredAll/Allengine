#include "input_handler.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "input_type.h"

using std::unique_ptr;
using std::make_unique;

InputHandler::InputHandler()
{
  keyboard_state = SDL_GetKeyboardState( NULL );
  current_input_type = InputType::none;
  previous_input_type = InputType::none;
}

void InputHandler::determine_input()
{
  previous_input_type = current_input_type;
  
  while( SDL_PollEvent( &e ))
  {
    if( e.type == SDL_KEYDOWN )
    {
      if( right_arrow( e ) )
      {
        current_input_type = InputType::right;
      }
      
      if( left_arrow( e ) )
      {
        current_input_type = InputType::left;
      }

      if( down_arrow( e ) )
      {
        current_input_type = InputType::down;
      }

      if( up_arrow( e ) )
      {
        current_input_type = InputType::up;
      }

      if( enter( e ) )
      {
        current_input_type = InputType::enter;
      }

      if( romeo( e ))
      {
        current_input_type = InputType::romeo;
      }

      if( escape( e ))
      {
        current_input_type = InputType::escape;
      }
    }

    if( e.type == SDL_KEYUP )
    {
      current_input_type = InputType::none;
    }

    if( e.type == SDL_QUIT )
    {
      current_input_type = InputType::escape;
    }
  }
  
  current_event = make_unique<InputEvent>( current_input_type, previous_input_type );  
}

InputEvent& InputHandler::handle_input()
{ 
  determine_input();
  return *current_event;
}

bool InputHandler::escape( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_ESCAPE;
}

bool InputHandler::right_arrow( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_RIGHT;
}

bool InputHandler::left_arrow( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_LEFT;
}

bool InputHandler::down_arrow( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_DOWN;
}

bool InputHandler::up_arrow( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_UP;
}

bool InputHandler::enter( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_RETURN;
}

bool InputHandler::romeo( SDL_Event e )
{
  return e.key.keysym.sym == SDLK_r;
}
