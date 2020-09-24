/**
   The functions in this file are due to Lazy Foo' Productions: 
   https://lazyfoo.net/tutorials/SDL/index.php
*/

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

void renderTexture(SDL_Texture *tex, 
                   SDL_Renderer *ren,
                   int x, 
                   int y, 
                   SDL_Rect *clip,
                   SDL_Rect *dst );

SDL_Texture* loadTexture(const std::string &file, 
                         SDL_Renderer *ren);

void renderTexture( SDL_Texture *tex, 
                    SDL_Renderer *ren,
                    SDL_Rect *dst, 
                    SDL_Rect *clip );

void renderTextureFlip( SDL_Texture *tex, 
                        SDL_Renderer *ren,
                        SDL_Rect *dst, 
                        SDL_Rect *clip );

void renderTextureFlip(SDL_Texture *tex, 
                       SDL_Renderer *ren,
                       int x, 
                       int y, 
                       SDL_Rect *clip );


