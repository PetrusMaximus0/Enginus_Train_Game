#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Library.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"

class GameObject
{
public:
	GameObject(SDL_Renderer* InRenderer, TransformComponent Transform);
	GameObject(SDL_Renderer* InRenderer, const char* TextureSheet, TransformComponent Transform);
	~GameObject();

	virtual void Update(float DeltaTime);
	virtual void Render();
	TransformComponent* GetTransformComponent();
	SpriteComponent* GetSpriteComponent();

protected:
	SDL_Renderer* Renderer;
	TransformComponent* TransformComp{};
	SpriteComponent* SpriteComp{};

};

