#ifndef JAREDALL_TETRIS_PIECE_SPRITE
#define JAREDALL_TETRIS_PIECE_SPRITE

#include "SDL_rect.h"
#include "SDL_render.h"
#include "cleanup.h"
#include "render_component.h"
#include "screen_coordinates.h"
#include "sprite_config.h"
#include "world_coordinates.h"
#include <memory>

class Sprite: public RenderComponent
{
public:
  
  Sprite( std::unique_ptr<WorldCoordinates> world_offset,
          int h,
          int w, 
          std::shared_ptr<SDL_Texture> texture );

  ~Sprite();

  std::shared_ptr<SDL_Texture> getTexture() const;
 
  std::shared_ptr<SDL_Rect> getDestination() const;
  
  std::shared_ptr<SDL_Rect> getClip() const;
  
  void set_clip( std::shared_ptr<SDL_Rect> clip );
  
  void set_destination( std::shared_ptr<SDL_Rect> destination );
  
  int get_h();
  
  int get_w();

  WorldCoordinates const& get_world_offset() const;

  ScreenCoordinates const& get_screen_location() const;

  void set_world_offset( int x, int y );

  void set_screen_location( std::unique_ptr<ScreenCoordinates> screen_location );

private:

  std::unique_ptr<WorldCoordinates> world_offset;
  std::unique_ptr<ScreenCoordinates> screen_location;
  std::shared_ptr<SDL_Texture> texture;
  std::shared_ptr<SDL_Rect> destination;
  std::shared_ptr<SDL_Rect> clip;

};

#endif
