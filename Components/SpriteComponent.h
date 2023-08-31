#pragma once
#include <SDL.h>
#include <SDL_image.h>


class SpriteComponent
{
public:
	SpriteComponent(SDL_Renderer* InRenderer);
	~SpriteComponent();

private:
	SDL_Renderer* Renderer{};
	SDL_Texture* Texture{};
	SDL_Rect SourceRectangle{}, DestinationRectangle{};
	float Heading{};

public:

	void SetTexture(const char* TexturePath);
	void SetSourceRectangle(int X, int Y, int W = GAME_OBJECT_WIDTH, int H = GAME_OBJECT_HEIGHT);
	void SetDestinationRectangle(int X, int Y, int W = GAME_OBJECT_WIDTH, int H = GAME_OBJECT_HEIGHT);
	void RenderSprite();
	void SetHeading(float Value);
};

