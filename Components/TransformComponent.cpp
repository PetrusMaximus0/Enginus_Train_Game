#include "TransformComponent.h"

TransformComponent::TransformComponent(Vector2D<float> InPosition = Vector2D<float>{ 0,0 }, Vector2D<float> InVelocity = Vector2D<float>{ 0,0 }, float InHeading = 0) :
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
	Position += Velocity*DeltaTime;
}

void TransformComponent::SetVelocity(Vector2D<float> NewVelocity) { Velocity = NewVelocity; }

void TransformComponent::SetPosition(Vector2D<float> NewPosition) { Position = NewPosition; }

void TransformComponent::SetHeading(float NewHeading) { Heading = NewHeading; }

Vector2D<float> TransformComponent::GetPosition() {return Position;}

Vector2D<float> TransformComponent::GetVelocity() {return Velocity;}

float TransformComponent::GetHeading() { return Heading; }

TransformComponent TransformComponent::GetTransform()
{
	return TransformComponent{Position, Velocity, Heading};
}
