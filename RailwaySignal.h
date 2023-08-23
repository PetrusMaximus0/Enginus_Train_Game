#pragma once
#include "GameObject.h"

class RailwaySignal : public GameObject 
{
private:
	Vector2D <int> TargetPosition;
	bool GreenLight = false;

protected:

public:
	RailwaySignal(SDL_Renderer* InRenderer, Vector2D<int> InCoordinates, Vector2D<int> InTargetPosition, bool InGreenLight);
	~RailwaySignal();
	void Update();
	void Render();
	void SetGreenLight(bool Value);
	bool GetGreenLight();
	Vector2D<int> GetTargetPosition();
};
