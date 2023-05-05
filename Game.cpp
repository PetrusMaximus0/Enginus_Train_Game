#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"


// 
//TEMPORARY GLOBALS

Map* GameWorld{};
RailwayPoint* Stations[20]{};
Train* Trains[5]{};

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
	/*Initialize SDL, window and renderer. Initialize the Textures*/
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
	SDL_PollEvent(&Event);
	
	switch (Event.type) {
	case SDL_QUIT:// in case of this event, the game is set to not running and thus the program will proceed to Game::Clean()
		IsRunning = false;
		break;
	default:
		break;

	}


}

void Game::Update()
{
	/*Updates the game state with new information */
	UpdateCounter++;
	//GameManager.Update();

	if (UpdateCounter % 500 == 0)
		Stations[2]->SwapNextPoint(Stations[6], Stations[3]);

	//if (UpdateCounter % 2000 == 0)
		//Stations[2]->SwapNextPoint(Stations[3], Stations[6]);



	for (int i = 0; i < StationsCounter; i++) {
		Stations[i]->Update();
	}
	/*Checks for collisions between trains*/
	CheckTrainCollision();
	/*Update Trains*/
	for (int i = 0; i < TrainsCounter; i++){
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
	for (auto& Stat : Stations) {
		delete(Stat);
	}
	delete GameWorld;
	std::cout << "Game cleaning complete" << std::endl;
}

bool Game::GetIsRunning(){return IsRunning;}

void Game::AddTile(int TileId, Vector2D<int> Coordinates) {


}

void Game::InitializeTrains() {
	/*Stations*/
	Stations[0] = Game::AddPoint("assets/art/waypoint_01.png", Vector2D<int>{4, 20}, "ST01", "WPT");
	Stations[1] = Game::AddPoint("assets/art/station_blue_01.png", Vector2D<int>{4, 12}, "ST02", "STA");
	Stations[2] = Game::AddPoint("assets/art/waypoint_01.png", Vector2D<int>{21, 12}, "ST03", "WPT");
	Stations[3] = Game::AddPoint("assets/art/station_blue_01.png", Vector2D<int>{39, 12}, "ST04", "STA");
	Stations[4] = Game::AddPoint("assets/art/waypoint_01.png", Vector2D<int>{39, 20}, "ST05", "WPT");
	Stations[5] = Game::AddPoint("assets/art/station_blue_01.png", Vector2D<int>{21, 20}, "ST06", "STA");
	Stations[6] = Game::AddPoint("assets/art/waypoint_01.png", Vector2D<int>{21, 4}, "ST07", "WPT");
	Stations[7] = Game::AddPoint("assets/art/station_blue_01.png", Vector2D<int>{10, 4}, "ST08", "STA");
	/*Lay Tracks*/
	ConnectPoints(Stations[0], Stations[1]);
	ConnectPoints(Stations[1], Stations[2]);
	ConnectPoints(Stations[2], Stations[3]);
	ConnectPoints(Stations[2], Stations[6]);
	ConnectPoints(Stations[3], Stations[4]);
	ConnectPoints(Stations[4], Stations[5]);
	ConnectPoints(Stations[5], Stations[0]);
	ConnectPoints(Stations[6], Stations[7]);
	/*Trains*/
	Trains[0] = Game::AddTrain(Stations[0], true, "CA", 5);
	Trains[1] = Game::AddTrain(Stations[1], true, "CP", 5);
};

RailwayPoint* Game::AddPoint(const char* TexturePath, Vector2D<int> Coordinates, const char* Identifier, const char* Type) {
	
	Coordinates.x = int(Coordinates.x * TILE_WIDTH);
	Coordinates.y = int(Coordinates.y * TILE_HEIGHT);
	StationsCounter++;
	return new RailwayPoint(Renderer, TexturePath, Coordinates, Identifier, Type);;

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

bool Game::SwapNextPoints(RailwayPoint* Station, RailwayPoint* PointA, RailwayPoint* PointB) {
	/*Check for collisions*/
	for (int i = 0; i < TrainsCounter; i++) {
		for (int j = 0; j < NUMBER_OF_CARS; j++) {
			if ((Trains[i]->GetCar(j)->GetPosition() - Station->GetPosition()).ManhatanAbs() < GAME_OBJECT_WIDTH * 2)
				return false;
		}
	}
	/*Call the point swapping*/
	Station->SwapNextPoint(PointA, PointB);
	return true;
}

int Game::CheckTrainCollision() {
	int NumberOfCollisions{ 0 };
	for (int i = 0; i < TrainsCounter && Trains[i]->GetIsMoving(); i++) {
		for (int j = i+1; j < TrainsCounter && Trains[i]->GetIsMoving(); j++){	
			for (int k = 0; k < NUMBER_OF_CARS && Trains[i]->GetIsMoving(); k++)
				/*Check for collisions between trains*/
				if ((Trains[i]->GetCar(0)->GetPosition() - Trains[j]->GetCar(k)->GetPosition()).ManhatanAbs() <= GAME_OBJECT_WIDTH) {
					Trains[i]->SetIsMoving(false);
					NumberOfCollisions++;
				}
		}
	}
	return NumberOfCollisions;
}