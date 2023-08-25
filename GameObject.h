#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Library.h"

constexpr int GAME_OBJECT_WIDTH{ 32 };
constexpr int GAME_OBJECT_HEIGHT{ 32 };

class GameObject
{
public:
	GameObject(SDL_Renderer* InRenderer, Vector2D<int> InCoordinates, GACarColor InColorType = GACarColor::Empty);
	GameObject(SDL_Renderer* InRenderer, const char* TextureSheet, Vector2D<int> InCoordinates, GACarColor InColorType = GACarColor::Empty);
	~GameObject();

	virtual void Update();
	virtual void Render();

	void SetTexture(SDL_Texture* NewTexture);
	void SetTransform(Vector2D<int> NewCoordinates, int NewHeading);
	void SetTransform(Vector2D<int> NewCoordinates);
	Vector2D<int> GetPosition();
	void SetColorType(GACarColor NewColorType);
	GACarColor GetColorType();

protected:
	SDL_Renderer* Renderer{};
	Vector2D<int> Coordinates{};
	SDL_Texture* Texture{};
	SDL_Rect SourceRectangle{}, DestinationRectangle{};
	int Heading{};//0 to 359 degrees clockwise rotation
	GACarColor ColorType{};

};

