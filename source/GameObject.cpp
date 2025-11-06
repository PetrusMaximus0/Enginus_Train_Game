#include "GameObject.h"

#include "SpriteComponent.h"
#include "TransformComponent.h"

GameObject::GameObject(SDL_Renderer *InRenderer, TransformComponent Transform) : Renderer(InRenderer) {
    TransformComp = new TransformComponent(Transform); //Implemented Delete
    SpriteComp = new SpriteComponent(InRenderer); //Implemented Delete
}

GameObject::GameObject(SDL_Renderer *InRenderer, const char *TextureSheet, TransformComponent Transform) : Renderer(
    InRenderer) {
    TransformComp = new TransformComponent(Transform); //Implemented Delete
    SpriteComp = new SpriteComponent(InRenderer); //Implemented Delete
}

GameObject::~GameObject() {
    /* don't need to set the pointer to nullptr because
    it will go out of scope right after.*/
    delete(TransformComp);
    delete(SpriteComp);
}

void GameObject::Update(float DeltaTime) {
    /*Updates the state of the object, movement, etc*/
    TransformComp->Update(DeltaTime);
}

void GameObject::Render() {
    //coordinates on the sprite sheet to take the texture from
    SpriteComp->SetSourceRectangle(0, 0);
    //Sets the position of the sprite
    SpriteComp->SetDestinationRectangle(TransformComp->GetPosition().x, TransformComp->GetPosition().y);
    //Sets the rotation of the sprite
    SpriteComp->SetHeading(TransformComp->GetHeading());
    /*Renders the sprite on screen*/
    SpriteComp->RenderSprite();
}

TransformComponent *GameObject::GetTransformComponent() { return TransformComp; }

SpriteComponent *GameObject::GetSpriteComponent() { return SpriteComp; }
