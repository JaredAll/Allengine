#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "SDL_rect.h"
#include "cleanup.h"
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

  virtual int get_x() = 0;

  virtual int get_y() = 0;

  virtual int get_h() = 0;

  virtual int get_w() = 0;

  virtual void set_x( int x ) = 0;

  virtual void set_y( int y ) = 0;

  virtual void calculate_destination() = 0;

  virtual ~RenderComponent() = default;

};

#endif
