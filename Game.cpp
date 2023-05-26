#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"
#include "assets/json_parser/json.hpp"
#include <fstream>

#define NUMBER_OF_STATIONS 100
#define MAX_NUMBER_OF_TRAINS 100

// 
//TEMPORARY GLOBALS

Map* GameWorld{};
RailwayPoint* Stations[NUMBER_OF_STATIONS]{};
Train* Trains[MAX_NUMBER_OF_TRAINS]{};

Game::Game() {
	/*Default constructor for class Game*/
	IsRunning = false;

	/*Initialize the Tiles for the Map*/
	for (int i = 0; i < GAME_WINDOW_HEIGHT / TILE_HEIGHT; i++) {
		for (int j = 0; j < GAME_WINDOW_WIDTH / TILE_WIDTH; j++) {
			GameMap[i][j] = TileTypes::Grass;
		}
	}
}

Game::~Game() {
	/*Default destructor for class Game*/
}

void Game::Init(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen)
{
	/*Initialize SDL, window and renderer. Initializes the trains and stations*/
	//full or windowed screen mode 
	int Flag{ 0 };
	IsFullscreen ? Flag = SDL_WINDOW_FULLSCREEN : false;
	
	//Initialize SDL window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized... " << std::endl;
		Window = SDL_CreateWindow(title, PositionX, PositionY, Width, Height, Flag);
		
		if (Window) {
			std::cout << "Window Created..." << std::endl;
			Renderer = SDL_CreateRenderer(Window, -1, 0);
			
			if (Renderer) {
				std::cout << "Renderer Created" << std::endl;
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				IsRunning = true;

			}
		}
	}

	InitializeTrains();

	GameWorld = new Map(Renderer);

}

void Game::HandleEvents(){
	/*Handles SDL events such as SDL_QUIT and others ( TBA )*/
	
	SDL_Event Event{};
	
	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {
		case SDL_QUIT:// in case of this event, the game is set to not running and thus the program will proceed to Game::Clean()
			IsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (Event.key.keysym.sym == SDLK_ESCAPE) {
				IsRunning = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (Event.button.button == SDL_BUTTON_LEFT) {
				HandleHitsUnderCursor();
			}
			break;

		default:
			break;

		}
	}
	



}

void Game::Update()
{
	/*Updates the game state with new information */
	UpdateCounter++;

/*Update Stations*/
	for (int i = 0; i < StationsCounter; i++) {
		Stations[i]->SetTrainInStation(IsTrainInStation(Stations[i]));
		Stations[i]->Update();
	}
/*Update Trains*/
	//check for collisions
	for (int i = 0; i < TrainsCounter; i++){
		for (int j = 0; j < TrainsCounter; j++) {
			if (i != j) {
				for (int k = 0; k < NUMBER_OF_CARS; k++)
					if ((Trains[i]->GetCar(0)->GetPosition() - Trains[j]->GetCar(k)->GetPosition()).Abs() <= GAME_OBJECT_WIDTH) {
						Trains[i]->SetIsMoving(false);
						break;
					}
			}	
		}
		//clean up trains marked for deletion
		if (Trains[i]->GetIsActive())
			Trains[i]->Update();
		else
			DeleteTrain(Trains[i]);
	}
}

void Game::Render()
{
	/*Renders the game elements with the SDL library */
	
	/*Clear old renderer stuff*/

	SDL_RenderClear(Renderer);
	GameWorld->LoadMap(GameMap);//Used to Change Maps

	/*Render the Game Map*/
	GameWorld->DrawMap();
	
	/*Render the Stations and Waypoints*/
	for (int i = 0; i < StationsCounter; i++) {
		Stations[i]->Render();
	}
	/*Render the Trains*/
	for (int i = 0; i < TrainsCounter; i++) {
		Trains[i]->Render();
	}

	//GameManager.Draw();
	/*Present everything on screen*/
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	/*Performs cleanup of SDL before calling SDL_Quit()*/
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	for (auto& Stat : Stations) delete(Stat);
	std::cout << "Cleared Stations\n";
	for (auto& Train : Trains) delete(Train);
	std::cout << "Cleared Trains\n";
	delete GameWorld;
	std::cout << "Cleared Map\n";
	std::cout << "Game cleaning complete!" << std::endl;
}

bool Game::GetIsRunning(){return IsRunning;}

void Game::AddTile(int TileId, Vector2D<int> Coordinates) {


}

void Game::InitializeTrains() {
	/*Load game data from a json file*/
	/*Load the json file*/
	using json = nlohmann::json;
	std::ifstream file("assets/levels/level_01.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open file!\n";
		IsRunning = false;
	}
	json Data;
	file >> Data;

	std::cout << Data.dump(4) << std::endl;
	int NumPoints = 0;
	int NumTrains = 0;

	/*Load Stations*/
	for (const auto& pointData : Data["points"]) {
		if (NumPoints > NUMBER_OF_STATIONS) {
			std::cerr << "Maximum points reached" << std::endl;
			IsRunning = false;
			break;
		}
		Vector2D<int> Coordinates;
		Coordinates.x = pointData["x"].get<int>();
		Coordinates.y = pointData["y"].get<int>();
		std::string Identifier{ pointData["identifier"].get<std::string>() };
		std::string  PointType{ pointData["pointType"].get<std::string>() };
		Stations[NumPoints] = Game::AddPoint(Coordinates, Identifier.c_str(), PointType.c_str());
		NumPoints++;
	}

	/*Lay Tracks*/
	NumPoints = 0;
	for (const auto& pointData : Data["points"]) {
		if (NumPoints > NUMBER_OF_STATIONS) {
			std::cerr << "Maximum points reached" << std::endl;
			IsRunning = false;
			break;
		}
		if (!pointData["routeA"].is_null()) {
			std::string RouteA = pointData["routeA"].get<std::string>();
			ConnectPoints(Stations[NumPoints], GetPointFromID(RouteA.c_str()));
		}
		if (!pointData["routeB"].is_null()) {
			std::string RouteA = pointData["routeB"].get<std::string>();
			ConnectPoints(Stations[NumPoints], GetPointFromID(RouteA.c_str()));
		}
		NumPoints++;
	}

	/*Add trains*/
	for (const auto& trainData : Data["trains"]) {
		bool ShoulMove = trainData["isMoving"];
		std::string Identifier = trainData["identifier"].get<std::string>();
		std::string InitialStationID = trainData["initialStationID"].get<std::string>();
		int MaxTrips = trainData["maxTrips"];
		Trains[NumTrains] = Game::AddTrain(GetPointFromID(InitialStationID.c_str()), ShoulMove, Identifier.c_str(), MaxTrips);
		NumTrains++;
	}
};

RailwayPoint* Game::AddPoint(Vector2D<int> Coordinates, const char* Identifier, const char* Type) {
	
	Coordinates.x = int(Coordinates.x * TILE_WIDTH);
	Coordinates.y = int(Coordinates.y * TILE_HEIGHT);
	StationsCounter++;
	return new RailwayPoint(Renderer, Coordinates, Identifier, Type);

}

void Game::DeletePoint(RailwayPoint* Point)
{
	/*Find every station that connects to this point and sever the connection*/
	for (int j = 0; j < StationsCounter; j++) {//iterate through every Station
		for (int i = 0; i < Stations[j]->GetAccessNumbers().y; i++) {//Iterate through the Exits
			if (Stations[j]->GetNextPoint(i) == Point) {//if it matches the point that we want
				DisconnectPoints(Stations[j], Point);//Remov the track from the map
				Stations[j]->ClearNextPoint(Point, i);//Sever the connection to this point
				break;
			}
		}
	}
	/*Swap this point with the last point in the array of points*/
	for (int j = 0; j < StationsCounter; j++) {
		if (Stations[j] == Point) {
			Stations[j] = Stations[StationsCounter - 1];
			Stations[StationsCounter - 1] = nullptr;
			StationsCounter--;
		}	
	}
	/*Delete this point*/
	delete(Point);

}

Train* Game::AddTrain(RailwayPoint* InitialStation, bool IsMoving, const char* Identifier, int MaxTrips)
{
	TrainsCounter++;
	return new Train(Renderer, IsMoving, Identifier, InitialStation, MaxTrips);

}

void Game::DeleteTrain(Train* Train)
{
	/*Swap with last element of train array*/
	for (int j = 0; j < TrainsCounter; j++) {
		if (Trains[j] == Train) {
			Trains[j] = Trains[TrainsCounter - 1];
			Trains[TrainsCounter - 1] = nullptr;
			TrainsCounter--;
		}
	}
	/*Delete the train*/
	delete(Train);

}

void Game::ConnectPoints(RailwayPoint* PointA, RailwayPoint* PointB) {
	
	PointA->SetNextPoint(PointB);
	
	/*Establish a direction*/
	Vector2D<int> CoordsA = PointA->GetPosition() / GAME_OBJECT_HEIGHT;
	Vector2D<int> CoordsB = PointB->GetPosition() / GAME_OBJECT_HEIGHT;
	Vector2D<int> Direction = CoordsB - CoordsA;
	int TrackCoordinate{};

	if (Direction.x != 0) {
		for (int i = 1; i < abs(Direction.x); i++) {
			TrackCoordinate = CoordsA.x + Direction.x / abs(Direction.x) * i;
			GameMap[CoordsA.y][TrackCoordinate] = TileTypes::TrackVertical;

		}
	}else if (Direction.y != 0) {
		for (int i = 1; i < abs(Direction.y); i++) {
			TrackCoordinate = CoordsA.y + Direction.y / abs(Direction.y) * i;
			GameMap[TrackCoordinate][CoordsA.x] = TileTypes::TrackHorizontal;
		}
	}

}

void Game::DisconnectPoints(RailwayPoint* PointA, RailwayPoint* PointB) {


}

void Game::HandleHitsUnderCursor() {
	/*Get the coordinates of the click*/
	int x, y;
	bool CanSwapLine{true};
	double DistanceToCursor{};
	SDL_GetMouseState(&x, &y);
	//std::cout << "Clicked Left mouse button at tile coordinates " << x << "," << y << std::endl;
	
	/*Check for train hit*/
	for (int i = 0; i < TrainsCounter; i++) {
		for (int j = 0; j < NUMBER_OF_CARS; j++) {
			DistanceToCursor = (Trains[i]->GetCar(j)->GetPosition() - Vector2D<int>{x-TILE_WIDTH/2, y-TILE_HEIGHT/2}).Abs();
			if (DistanceToCursor <= TILE_HEIGHT/2) {
				std::cout << "Distance to cursor = " << DistanceToCursor << std::endl;
				Trains[i]->SetIsMoving(!Trains[i]->GetIsMoving());
			}
		}
	}
	/*Check for station hit and handle line swapping*/
	for (int i = 0; i < StationsCounter; i++) {
		if ((Stations[i]->GetPosition() - Vector2D<int>{x - TILE_WIDTH / 2, y - TILE_HEIGHT / 2}).Abs() <= TILE_HEIGHT/2) {
			for (int k = 0; k < TrainsCounter; k++) {//check if any train is at the station
				for (int j = 0; j < NUMBER_OF_CARS; j++) {//check per car
					if ((Trains[k]->GetCar(j)->GetPosition() - Stations[i]->GetPosition()).Abs() <= TILE_HEIGHT/2) {
						CanSwapLine = false;// if there is a car at the station we must not swap lines
					}
				}
			}
			if(!Stations[i]->GetIsTrainInStation())//No cars at the station means we can swap lines
				Stations[i]->SwapNextPoint(Stations[i]->GetNextPoint(1), Stations[i]->GetNextPoint(1));
		
		}
			
	}
	/*...Other types*/
	/*Nothing was clicked*/
}

bool Game::IsTrainInStation(RailwayPoint* Station) {
		for (int j = 0; j < TrainsCounter; j++) {
			for (int k = 0; k < NUMBER_OF_CARS; k++) {
				if ((Station->GetPosition() - Trains[j]->GetCar(k)->GetPosition()).Abs() < GAME_OBJECT_HEIGHT) {
					return true;
				}
			}
		}
		return false;
}

RailwayPoint* Game::GetPointFromID(const char* ID) {
	for (int i = 0; i < StationsCounter; i++)
		if (strcmp(ID, Stations[i]->GetIdentifier()) == 0)
			return Stations[i];
	return nullptr;
}