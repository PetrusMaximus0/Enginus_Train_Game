#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Library.h"

#define GAME_OBJECT_WIDTH 32
#define GAME_OBJECT_HEIGHT 32

class GameObject
{
public:
	GameObject(SDL_Renderer* InRenderer, const char* TextureSheet, Vector2D<int> InCoordinates);
	~GameObject();

	virtual void Update();
	virtual void Render();

private:
	SDL_Renderer* Renderer{};
	Vector2D<int> Coordinates{};
	SDL_Texture* Texture{};
	SDL_Rect SourceRectangle{}, DestinationRectangle{};
	int Heading{};//0 to 359 degrees clockwise rotation
	
};

