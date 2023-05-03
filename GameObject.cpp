#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(SDL_Renderer* InRenderer, const char* TextureSheet, Vector2D<int> InCoordinates):
	Coordinates(InCoordinates), 
	Renderer(InRenderer), 
	Texture(TextureManager::LoadTexture(Renderer, TextureSheet)){}

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
	SourceRectangle.w = GAME_OBJECT_WIDTH;
	SourceRectangle.h = GAME_OBJECT_HEIGHT;
	//Where to draw the texture?
	DestinationRectangle.x = Coordinates.x;
	DestinationRectangle.y = Coordinates.y;
	//Scaling the texture, only use powers of 2 for division or multiplication
	DestinationRectangle.w = SourceRectangle.w * 1;
	DestinationRectangle.h = SourceRectangle.h * 1;

}

void GameObject::Render()
{	/*Renders the game object on screen*/
	SDL_RenderCopyEx(Renderer, Texture, &SourceRectangle, &DestinationRectangle, Heading, NULL, SDL_FLIP_NONE);
	
}
