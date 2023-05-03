#pragma once
#include "GameObject.h"

class RailwayPoint : public GameObject
{
private:
	char Identifier[4]{};
	char Type[3]{};//station STA or waypoint WPT
	int Size{};
	int NumberOfEntries{};
	int NumberOfExits{};

public:
	RailwayPoint(SDL_Renderer* InRenderer, const char* TextureSheet, Vector2D<int> InCoordinates);
	~RailwayPoint();
	void InitializePoint();
	void ConnectPoints();
	void DisconnectPoints();
	void Update() override;
	void Render() override;
};

