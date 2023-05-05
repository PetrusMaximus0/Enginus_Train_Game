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

	RailwayPoint* AddPoint(const char* TexturePath, Vector2D<int> Coordinates, const char* Identifier, const char* Type);
	void DeletePoint(RailwayPoint* Point);
	Train* AddTrain(RailwayPoint* InitialStation, bool IsMoving, const char* Identifier, int MaxTrips);
	void DeleteTrain(Train* Train);
	void ConnectPoints(RailwayPoint* PointA, RailwayPoint* PointB);
	void DisconnectPoints(RailwayPoint* PointA, RailwayPoint* PointB);
	bool SwapNextPoints(RailwayPoint* Station, RailwayPoint* PointA, RailwayPoint* PointB);
   	int CheckTrainCollision();

private:
	SDL_Renderer* Renderer{};
	bool IsRunning{};
	SDL_Window* Window{};
	int UpdateCounter{0};
	int StationsCounter{0};
	int TrainsCounter{0};
	TileTypes GameMap[GAME_WINDOW_HEIGHT / TILE_HEIGHT][GAME_WINDOW_WIDTH / TILE_WIDTH]{};
};
