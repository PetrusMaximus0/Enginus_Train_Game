#pragma once
#include "source/Library.h"

class TransformComponent 

{
public:
	TransformComponent(Vector2D<float> InPosition, Vector2D<float> InVelocity, float InHeading);
	~TransformComponent();

private:
	Vector2D<float> Position{ 0.f, 0.f };
	Vector2D<float> Velocity{ 0.f, 0.f };
	
	//float RotationSpeed{ 0 };
	float Heading{ 0.f }; //degrees

public:
	//Updates position based on velocity.
	void Update(float DeltaTime);

	//Sets a new Velocity.
	void SetVelocity(Vector2D<float> NewVelocity);

	//Set a new position
	void SetPosition(Vector2D<float> NewPosition);

	//set a new Heading
	void SetHeading(float NewHeading);

	//Get current Position
	Vector2D<float> GetPosition();

	//Get Velocity
	Vector2D<float> GetVelocity();

	//Get Heading
	float GetHeading();

	//Get Whole Transform
	TransformComponent GetTransform();

};
