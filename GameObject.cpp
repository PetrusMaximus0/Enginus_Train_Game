#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* TextureSheet, Vector2DInt InCoordinates, bool IsStatic)
{
	Texture = TextureManager::LoadTexture(TextureSheet);
	Coordinates = InCoordinates;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	/*Updates the state of the object, movement, etc*/
	//Manage Coordinates of Object
	Coordinates.x += 0;
	Coordinates.y += 0;
	//coordinates on the sprite sheet to take texture from
	SourceRectangle.x = 0;
	SourceRectangle.y = 0;
	SourceRectangle.w = 64;
	SourceRectangle.h = 64;
	//Where to draw the texture?
	DestinationRectangle.x = Coordinates.x;
	DestinationRectangle.y = Coordinates.y;
	//Scaling the texture, only use powers of 2 for division or multiplication
	DestinationRectangle.w = SourceRectangle.w * 1;
	DestinationRectangle.h = SourceRectangle.h * 1;

}

void GameObject::Render()
{	/*Renders the game object on screen*/
	
	SDL_RenderCopyEx(Game::Renderer, Texture, &SourceRectangle, &DestinationRectangle, Heading, NULL, SDL_FLIP_NONE);
	
}
