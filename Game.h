#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include "Map.h"
#include "Library.h"
#include "Train.h"
#include "RailwayPoint.h"
#include "RailwaySignal.h"
#include "assets/json_parser/json.hpp"

class Game{
public:
	Game(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen, const int FramesPerSecond);
	~Game();
	void HandleEvents();
	void Update(float DeltaTime);
	void Render();
	void Clean();
	bool GetIsRunning();
	//
	nlohmann::json LoadGameData();
	//
	void InitializeSDL(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen);
	void InitializePoints(nlohmann::json Data);
	void InitializeTrains(nlohmann::json Data);
	void InitializeSignals(nlohmann::json Data);
	//
	RailwayPoint* NewPoint(Vector2D<float> Coordinates, const char* Identifier, const char* Type);
	void DeletePoint(RailwayPoint* Point);
	void ConnectPoints(RailwayPoint* PointA, RailwayPoint* PointB);
	RailwayPoint* GetPointFromID(const char* ID);
	//
	void HandleHitsUnderCursor();
	//
	void UpdateTrains(float DeltaTime);
	Train* NewTrain(RailwayPoint* InitialStation, bool IsMoving, const char* Identifier, int MaxTrips);
	void DeleteTrain(Train* Train);
	bool IsTrainInStation(RailwayPoint* Station);
	/*returns true if object 1 is colliding with object 2 and false otherwise*/
	bool IsColliding(TransformComponent Object1Transform, TransformComponent Object2Transform);
	//
	RailwaySignal* NewSignal(Vector2D<float> Position, Vector2D<float> TargetPosition, bool GreenLight);
	void DeleteSignal(RailwaySignal* Signal);
	
private:
	SDL_Renderer* Renderer{};
	bool IsRunning{};
	SDL_Window* Window{};
	int UpdateCounter{0};
	int StationsCounter{0};
	int TrainsCounter{0};
	int SignalsCounter{0};
	const int FramesPerSecond{};
	TileTypes GameMap[GAME_WINDOW_HEIGHT / TILE_HEIGHT][GAME_WINDOW_WIDTH / TILE_WIDTH]{};
	Map* GameWorld{};
	RailwayPoint* Stations[NUMBER_OF_STATIONS]{};
	Train* Trains[MAX_NUMBER_OF_TRAINS]{};
	RailwaySignal* TrafficSignals[MAX_NUMBER_OF_TRAFFIC_SIGNS]{};

};
