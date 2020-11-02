#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "SDL_rect.h"
#include "cleanup.h"
#include "screen_coordinates.h"
#include "world_coordinates.h"
#include <SDL.h>
#include <iostream>
#include <memory>
#include <type_traits>

class RenderComponent
{
public:

  virtual std::shared_ptr<SDL_Texture> getTexture() const = 0; 

  virtual std::shared_ptr<SDL_Rect> getDestination() const = 0;

  virtual std::shared_ptr<SDL_Rect> getClip() const = 0;

  virtual void set_clip( std::shared_ptr<SDL_Rect> clip ) = 0;

  virtual void set_destination( std::shared_ptr<SDL_Rect> destination ) = 0;

  virtual int get_h() const = 0;

  virtual int get_w() const = 0;

  virtual WorldCoordinates const& get_world_offset() const = 0;

  virtual ScreenCoordinates const& get_screen_location() const = 0;

  virtual void set_world_offset( int x, int y ) = 0;

  virtual void set_screen_location( std::unique_ptr<ScreenCoordinates> screen_location ) = 0;

  virtual ~RenderComponent() = default;

};

#endif
