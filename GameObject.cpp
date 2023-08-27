#include "GameObject.h"
//#include "TextureManager.h"

GameObject::GameObject(SDL_Renderer* InRenderer, TransformComponent&& Transform, GACarColor InColorType):
	Renderer(InRenderer),
	ColorType(InColorType)
{
	TransformComp = new TransformComponent(Transform);//Implemented Delete
}

GameObject::GameObject(SDL_Renderer* InRenderer, const char* TextureSheet, TransformComponent&& Transform, GACarColor InColorType):
	Renderer(InRenderer),
	Texture(TextureManager::LoadTexture(Renderer, TextureSheet)),
	ColorType(InColorType)
{
	TransformComp = new TransformComponent(Transform);//Implemented Delete
}

GameObject::~GameObject()
{
	/* don't need to set the pointer to nullptr because 
	it will go out of scope right after.*/
	delete(TransformComp);

}

void GameObject::Update(float DeltaTime)
{

	/*Updates the state of the object, movement, etc*/
	TransformComp->Update(DeltaTime);

	//coordinates on the sprite sheet to take texture from
	SourceRectangle.x = 0;
	SourceRectangle.y = 0;
	SourceRectangle.w = GAME_OBJECT_WIDTH;
	SourceRectangle.h = GAME_OBJECT_HEIGHT;
	//Where to draw the texture?
	DestinationRectangle.x = TransformComp->GetPosition().x;
	DestinationRectangle.y = TransformComp->GetPosition().y;
	//Scaling the texture, only use powers of 2 for division or multiplication
	DestinationRectangle.w = SourceRectangle.w * 1;
	DestinationRectangle.h = SourceRectangle.h * 1;

}

void GameObject::Render()
{	/*Renders the game object on screen*/
	SDL_RenderCopyEx(Renderer, Texture, &SourceRectangle, &DestinationRectangle, Heading, NULL, SDL_FLIP_NONE);
	
}

void GameObject::SetTexture(SDL_Texture* NewTexture)
{
	SDL_DestroyTexture(Texture);
	Texture = NewTexture;
}

void GameObject::SetColorType(GACarColor NewColorType)
{
	ColorType = NewColorType;
}

GACarColor GameObject::GetColorType() {
	return ColorType;
}

TransformComponent* GameObject::GetTransformComponent()
{
	return TransformComp;
}
