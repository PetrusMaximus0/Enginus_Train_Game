#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include "Library.h"
#include "Train.h"
#include "RailwayPoint.h"

class Game{
public:
	Game();
	~Game();
	void Init(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool GetIsRunning();
	void AddTile(int TileId, Vector2D<int> Coordinates);
	void InitializeTrains();
	

private:
	SDL_Renderer* Renderer{};
	bool IsRunning{};
	SDL_Window* Window{};
	int UpdateCounter{};
	//these should really be initialized
	Train Trains[10];
	//these should really be initialized
	RailwayPoint RailwayPoints[10];
};
