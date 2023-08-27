#include "TransformComponent.h"

TransformComponent::TransformComponent(Vector2D<int> InPosition = Vector2D<int>{ 0,0 }, Vector2D<int> InVelocity = Vector2D<int>{ 0,0 }, float InHeading = 0) :
	Position(InPosition), 
	Velocity(InVelocity), 
	Heading(InHeading)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update(float DeltaTime)
{
	Position += Velocity;
}

void TransformComponent::SetVelocity(Vector2D<int> NewVelocity) { Velocity = NewVelocity; }

void TransformComponent::SetPosition(Vector2D<int> NewPosition) { Position = NewPosition; }

void TransformComponent::SetHeading(float NewHeading) { Heading = NewHeading; }

Vector2D<int> TransformComponent::GetPosition() {return Position;}

Vector2D<int> TransformComponent::GetVelocity() {return Velocity;}

float TransformComponent::GetHeading() { return Heading; }