#ifndef CLEANUP_H
#define CLEANUP_H

#include "SDL_render.h"
#include "SDL_video.h"
#include <utility>
#include <SDL.h>

struct SDL_Rect_Destroyer
{
void operator()( SDL_Rect* rect ) const
  {
    free( rect );
  }  
};

struct SDL_Renderer_Destroyer
{
  void operator()( SDL_Renderer* renderer ) const
  {
    SDL_DestroyRenderer( renderer );
  }
};

struct SDL_Window_Destroyer
{
  void operator()( SDL_Window* window ) const
  {
    SDL_DestroyWindow( window );
  }
};

struct SDL_Texture_Destroyer
{
  void operator()( SDL_Texture* texture ) const
  {
    SDL_DestroyTexture( texture );
  }
};

struct SDL_Surface_Destroyer
{
  void operator()( SDL_Surface* surface ) const
  {
    SDL_FreeSurface( surface );
  }
};


#endif
