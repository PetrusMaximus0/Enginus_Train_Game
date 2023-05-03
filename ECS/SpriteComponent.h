#pragma once
#include "Components.h"
#include <SDL.h>
#include "../TextureManager.h"

class SpriteComponent : public Component {
private:
	PositionComponent* Position;
	SDL_Texture* Texture;
	SDL_Rect SourceRectangle, DestinationRectangle;
	SDL_Renderer* Renderer;

public:
	SpriteComponent() = default;
	SpriteComponent(SDL_Renderer* InRenderer, const char* TexturePath): 
		Renderer(InRenderer){
		
		SetTexture(TexturePath);
	}

	void Init() override{

		Position = &OwnerEntity->GetComponent<PositionComponent>();
		
		SourceRectangle.x = SourceRectangle.y = 0;
		SourceRectangle.w = SourceRectangle.h = 32;
		DestinationRectangle.w = DestinationRectangle.h = 64;
	}

	void Update() override{
		DestinationRectangle.x = Position->GetPosition().x;
		DestinationRectangle.y = Position->GetPosition().y;
	}

	void Draw() override {
		TextureManager::Draw(Renderer, Texture, SourceRectangle, DestinationRectangle);
	}

	void SetTexture(const char* NewTexturePath) {
		Texture = TextureManager::LoadTexture(Renderer, NewTexturePath);
	}

};
