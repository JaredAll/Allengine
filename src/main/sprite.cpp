#include "sprite.h"
#include "SDL_rect.h"

using namespace std;

Sprite::Sprite( int param_x,
                int param_y,
                int param_h,
                int param_w,
                shared_ptr<SDL_Texture> param_texture )
  : texture( param_texture )
{
  destination = make_shared<SDL_Rect>();
  destination -> x = param_x;
  destination -> y = param_y;
  destination -> h = param_h;
  destination -> w = param_w;
}

Sprite::~Sprite()
{
}

shared_ptr<SDL_Texture> Sprite::getTexture() const
{
  return texture;
}

shared_ptr<SDL_Rect> Sprite::getDestination() const
{
  return destination;
}

shared_ptr<SDL_Rect> Sprite::getClip() const
{
  return clip;
}

void Sprite::set_clip( shared_ptr<SDL_Rect> param_clip ) 
{
  clip = param_clip;
}

void Sprite::set_destination( shared_ptr<SDL_Rect> param_destination )
{
  destination = param_destination;
}

int Sprite::get_x()
{
  return destination -> x;
}

int Sprite::get_y()
{
  return destination -> y;
}

int Sprite::get_h()
{
  return destination -> h;
}

int Sprite::get_w()
{
  return destination -> w;
}


void Sprite::set_x( int param_x )
{
  destination -> x = param_x;
}

void Sprite::set_y( int param_y )
{
  destination -> y = param_y;
}

void Sprite::calculate_destination()
{
}

