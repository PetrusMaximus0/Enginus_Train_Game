#include "SpriteComponent.h"
#include "../TextureManager.h"

SpriteComponent::SpriteComponent(SDL_Renderer* InRenderer):
	Renderer(InRenderer)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::SetTexture(const char* TexturePath)
{
	Texture = TextureManager::LoadTexture(Renderer, TexturePath);
}

void SpriteComponent::SetSourceRectangle(int X, int Y, int W, int H)
{
	SourceRectangle.x = X;
	SourceRectangle.y = Y;
	SourceRectangle.w = W;
	SourceRectangle.h = H;
}

void SpriteComponent::SetDestinationRectangle(int X, int Y, int W, int H)
{
	DestinationRectangle.x = X;
	DestinationRectangle.y = Y;
	DestinationRectangle.w = W;
	DestinationRectangle.h = H;

}

void SpriteComponent::RenderSprite()
{
	SDL_RenderCopyEx(Renderer, Texture, &SourceRectangle, &DestinationRectangle, Heading, NULL, SDL_FLIP_NONE);
}

void SpriteComponent::SetHeading(float Value)
{
	Heading = Value;
}
