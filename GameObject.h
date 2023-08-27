#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Library.h"
#include "Components/TransformComponent.h"

constexpr int GAME_OBJECT_WIDTH{ 32 };
constexpr int GAME_OBJECT_HEIGHT{ 32 };

class GameObject
{
public:
	GameObject(SDL_Renderer* InRenderer, TransformComponent&& Transform, GACarColor InColorType = GACarColor::Empty);
	GameObject(SDL_Renderer* InRenderer, const char* TextureSheet, TransformComponent&& Transform, GACarColor InColorType = GACarColor::Empty);
	~GameObject();

	virtual void Update(float DeltaTime);
	virtual void Render();
	void SetTexture(SDL_Texture* NewTexture);
	void SetColorType(GACarColor NewColorType);
	GACarColor GetColorType();
	TransformComponent* GetTransformComponent();

protected:
	TransformComponent* TransformComp{};
	
	SDL_Renderer* Renderer{};
	SDL_Texture* Texture{};
	SDL_Rect SourceRectangle{}, DestinationRectangle{};

	int Heading{};//0 to 359 degrees clockwise rotation
	GACarColor ColorType{};

};

