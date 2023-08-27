#pragma once
#include "../Library.h"

class TransformComponent 

{
public:
	TransformComponent(Vector2D<int> InPosition, Vector2D<int> InVelocity, float InHeading);
	~TransformComponent();

private:
	Vector2D<int> Position{ 0,0 };
	Vector2D<int> Velocity{ 0,0 };
	float Heading{0}; //degrees

public:
	//Updates position based on velocity.
	void Update(float DeltaTime);
	
	//Sets a new Velocity.
	void SetVelocity(Vector2D<int> NewVelocity);

	//Set a new position
	void SetPosition(Vector2D<int> NewPosition);

	//set a new Heading
	void SetHeading(float NewHeading);

	//Get current Position
	Vector2D<int> GetPosition();

	//Get Velocity
	Vector2D<int> GetVelocity();

	//Get Heading
	float GetHeading();


};