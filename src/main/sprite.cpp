#include "sprite.h"
#include "SDL_rect.h"
#include <memory>
#include <type_traits>

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

Sprite::Sprite( unique_ptr<WorldCoordinates> world_offset_param,
                int param_h,
                int param_w,
                shared_ptr<SDL_Texture> param_texture )
  : world_offset( move( world_offset_param ) ), texture( param_texture )
{
  destination = make_shared<SDL_Rect>();
  destination -> x = 0;
  destination -> y = 0;
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

WorldCoordinates const& Sprite::get_world_offset() const
{
  return *world_offset;
}

ScreenCoordinates const& Sprite::get_screen_location() const
{
  return *screen_location;
}

int Sprite::get_h() const
{
  return destination -> h;
}

int Sprite::get_w() const
{
  return destination -> w;
}

void Sprite::set_world_offset( int x, int y )
{
  world_offset = make_unique<WorldCoordinates>( x, y );
}

void Sprite::set_screen_location( unique_ptr<ScreenCoordinates> screen_location_param )
{
  screen_location = move( screen_location_param );

  destination -> x = screen_location -> get_screen_x();
  destination -> y = screen_location -> get_screen_y();
}
