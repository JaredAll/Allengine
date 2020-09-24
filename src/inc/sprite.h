#ifndef JAREDALL_TETRIS_PIECE_SPRITE
#define JAREDALL_TETRIS_PIECE_SPRITE

#include "SDL_rect.h"
#include "SDL_render.h"
#include "cleanup.h"
#include "render_component.h"
#include "sprite_config.h"

class Sprite: public RenderComponent
{
public:
  
  Sprite( int x, int y, int h, int w, std::shared_ptr<SDL_Texture> texture );

  ~Sprite();

  std::shared_ptr<SDL_Texture> getTexture() const;
 
  std::shared_ptr<SDL_Rect> getDestination() const;
  
  std::shared_ptr<SDL_Rect> getClip() const;
  
  void set_clip( std::shared_ptr<SDL_Rect> clip );
  
  void set_destination( std::shared_ptr<SDL_Rect> destination );
  
  int get_x();
  
  int get_y();

  int get_h();
  
  int get_w();
  
  void set_x( int x );
  
  void set_y( int y );
  
  void calculate_destination();

private:
  
  std::shared_ptr<SDL_Texture> texture;
  std::shared_ptr<SDL_Rect> destination;
  std::shared_ptr<SDL_Rect> clip;

};

#endif
