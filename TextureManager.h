#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class TextureManager{

public:
	//If successful returns a pointer to an sdl_texture. Returns nullptr otherwise.
	static SDL_Texture* LoadTexture(SDL_Renderer* Renderer, const char* FileName);
	static void Draw(SDL_Renderer* Renderer, SDL_Texture* Texture, SDL_Rect Source, SDL_Rect Destination, double Heading = 0.f);

};

