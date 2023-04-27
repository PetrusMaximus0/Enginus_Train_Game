#pragma once
#include "Game.h"
class GameObject
{
public:
	GameObject(const char* TextureSheet, Vector2DInt InCoordinates, bool IsStatic = true);
	~GameObject();

	void Update();
	void Render();

private:
	
	Vector2DInt Coordinates{};
	SDL_Texture* Texture{};
	SDL_Rect SourceRectangle{}, DestinationRectangle{};
	int Heading{};//0 to 359 degrees clockwise rotation
	
};

