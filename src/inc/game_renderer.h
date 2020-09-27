#ifndef JAREDALL_TETRIS_GAME_RENDERER_H
#define JAREDALL_TETRIS_GAME_RENDERER_H

#include "cleanup.h"
#include "game_component.h"
#include "render_component.h"
#include <type_traits>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include "easy_sdl.h"

template< typename, typename = std::void_t<>>
struct IsRenderableT : std::false_type
{};

template< typename T>
struct IsRenderableT< T, std::void_t< decltype( std::declval<T>().get_render_components())>>
  : std::true_type
{};

class GameRenderer
{
public:
  
  GameRenderer( std::unique_ptr<SDL_Window, SDL_Window_Destroyer> win );

  std::shared_ptr<SDL_Texture> create_texture( std::string image_path );

  std::shared_ptr<SDL_Texture> render_letter_texture( TTF_Font* font,
                                                      char letter_singleton[],
                                                      SDL_Color color);
  template< typename T >
  void render( std::vector<std::unique_ptr<T>>& components )
  {
    render_implementation( components, IsRenderableT<T>{} );
  }

private:

  template< typename T >
  void render_implementation( std::vector<std::unique_ptr<T>>& components,
                              std::true_type )
  {
    SDL_RenderClear( renderer.get() );

    for( auto& component : components )
    {
      render_all( (*component).get_render_components() );
    }

    SDL_RenderPresent( renderer.get() );
  }

  template< typename T, typename = typename std::enable_if_t<
                          std::is_base_of<RenderComponent, T>::value>>
  void render_all( std::vector<std::unique_ptr<T>>& render_components )
  {
    for( size_t i = 0; i < render_components.size(); i++ )
    {
      render_component( *render_components.at( i ) );
    }
  }

  template< typename T >
  void render_component( const T& renderComponent )
  {
    if( renderComponent.get_screen_location().is_visible() )
    {
      renderTexture( renderComponent.getTexture().get(),
                     renderer.get(),
                     renderComponent.getDestination().get(),
                     renderComponent.getClip().get() );  
    }
  }

  std::unique_ptr<SDL_Window, SDL_Window_Destroyer> window;

  std::unique_ptr<SDL_Renderer, SDL_Renderer_Destroyer> renderer;
};

#endif
