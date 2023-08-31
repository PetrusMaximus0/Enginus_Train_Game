#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include <fstream>

Map* GameWorld{};
RailwayPoint* Stations[NUMBER_OF_STATIONS]{};
Train* Trains[MAX_NUMBER_OF_TRAINS]{};
RailwaySignal* TrafficSignals[MAX_NUMBER_OF_TRAFFIC_SIGNS]{};

Game::Game(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen) {
	/*Default constructor for class Game*/
	IsRunning = false;

	/*Initialize the Tiles for the Map*/
	for (int i = 0; i < GAME_WINDOW_HEIGHT / TILE_HEIGHT; i++) {
		for (int j = 0; j < GAME_WINDOW_WIDTH / TILE_WIDTH; j++) {
			GameMap[i][j] = TileTypes::Grass;
		}
	}

	InitializeSDL(title, PositionX, PositionY, Width, Height, IsFullscreen);

	nlohmann::json Data = LoadGameData();
	InitializePoints(Data);
	InitializeTrains(Data);
	InitializeSignals(Data);

	GameWorld = new Map(Renderer);
}
Game::~Game() {
	/*Default destructor for class Game*/
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
void Game::Update(float DeltaTime)
{
	/*Updates the game state with new information */
	UpdateCounter++;

/*Update Stations*/
	for (int i = 0; i < StationsCounter; i++) {
		Stations[i]->SetTrainInStation(IsTrainInStation(Stations[i]));
		Stations[i]->Update(DeltaTime);
	}
/*Update Trains*/
	//check for collisions between trains
	for (int i = 0; i < TrainsCounter; i++){
		for (int j = 0; j < TrainsCounter; j++) {
			if (i != j) {
				for (int k = 0; k < NUMBER_OF_CARS; k++)
					if ((Trains[i]->GetCar(0)->GetTransformComponent()->GetPosition() - Trains[j]->GetCar(k)->GetTransformComponent()->GetPosition()).Abs() <= GAME_OBJECT_WIDTH) {
						Trains[i]->TemporaryStop(1.5f*200);
						break;
					}
			}	
		}
		//clean up trains marked for deletion
		if (Trains[i]->GetIsActive())
			Trains[i]->Update(DeltaTime);
		else
			DeleteTrain(Trains[i]);
	}
/*Update Traffic Lights*/

	//check for collisions between traffic signs and trains and update
	for (int i = 0; i < SignalsCounter; i++) {
		if (!TrafficSignals[i]->GetGreenLight()) {
			for (int j = 0; j < TrainsCounter; j++) {
				if ((TrafficSignals[i]->GetTargetPosition() - Trains[j]->GetCar(0)->GetTransformComponent()->GetPosition()).Abs() < TILE_HEIGHT) {
					Trains[j]->TemporaryStop(1.5f*200);
				}
			}
		}
		TrafficSignals[i]->Update(DeltaTime);
		
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

	/*Render the Signals*/
	for (int i = 0; i < SignalsCounter; i++) {
		TrafficSignals[i]->Render();
	}

	/*Render the Trains*/
	for (int i = 0; i < TrainsCounter; i++) {
		Trains[i]->Render();
	}

	/*Present everything on screen*/
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	/*Performs cleanup of SDL before calling SDL_Quit()*/
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	for (auto& Signal : TrafficSignals) DeleteSignal(Signal);
	std::cout << "Cleared Traffic Signals\n";
	for (auto& Stat : Stations) DeletePoint(Stat);
	std::cout << "Cleared Stations\n";
	for (auto& Train : Trains) DeleteTrain(Train);
	std::cout << "Cleared Trains\n";
	delete GameWorld;
	std::cout << "Cleared Map\n";
	std::cout << "Game cleaning complete!" << std::endl;
}
bool Game::GetIsRunning(){return IsRunning;}

nlohmann::json Game::LoadGameData()
{
	/*Load game data from a json file*/
	/*Load the json file*/
	using json = nlohmann::json;
	std::ifstream file("assets/levels/level_00.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open file!\n";
		IsRunning = false;
	}
	json Data;
	file >> Data;
	std::cout << Data.dump(4) << std::endl;
	return Data;
}
void Game::InitializeSDL(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen)
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


}
void Game::InitializePoints(nlohmann::json Data)
{
	int NumPoints{};
	
	/*Load Stations*/
	for (const auto& pointData : Data["points"]) {
		if (NumPoints > NUMBER_OF_STATIONS) {
			std::cerr << "Maximum points reached" << std::endl;
			IsRunning = false;
			break;
		}
		Vector2D<float> Coordinates{};
		Coordinates.x = pointData["x"].get<float>();
		Coordinates.y = pointData["y"].get<float>();
		std::string Identifier{ pointData["identifier"].get<std::string>() };
		std::string  PointType{ pointData["pointType"].get<std::string>() };


		Stations[NumPoints] = Game::NewPoint(Coordinates, Identifier.c_str(), PointType.c_str());
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
}
void Game::InitializeTrains(nlohmann::json Data) {
	/*Add trains*/
	int NumTrains{};

	for (const auto& trainData : Data["trains"]) {
		bool ShoulMove = trainData["isMoving"];
		std::string Identifier = trainData["identifier"].get<std::string>();
		std::string InitialStationID = trainData["initialStationID"].get<std::string>();
		int MaxTrips = trainData["maxTrips"];
		Trains[NumTrains] = Game::AddTrain(GetPointFromID(InitialStationID.c_str()), ShoulMove, Identifier.c_str(), MaxTrips);
		NumTrains++;
	}
}
void Game::InitializeSignals(nlohmann::json Data)
{
	/*Add signals*/
	int NumSignals{};
	for (const auto& signalData : Data["signals"]) {
		bool GreenLight = signalData["greenLight"];

		Vector2D<float> Coordinates;
		Coordinates.x = signalData["positionX"].get<int>();
		Coordinates.y = signalData["positionY"].get<int>();

		Vector2D<float> TargetCoordinates;
		TargetCoordinates.x = signalData["targetX"].get<int>();
		TargetCoordinates.y = signalData["targetY"].get<int>();

		TrafficSignals[NumSignals] = Game::NewSignal(Coordinates, TargetCoordinates, GreenLight);
		NumSignals++;
	}
}

RailwayPoint* Game::NewPoint(Vector2D<float> Coordinates, const char* Identifier, const char* Type) {
	
	Coordinates = TileToPixelCoordinates(Coordinates);
	StationsCounter++;
	return new RailwayPoint(Renderer, TransformComponent{ Coordinates, Vector2D<float>{0,0}, 0.f }, Identifier, Type);

} 

void Game::DeletePoint(RailwayPoint* Point)
{
	/*Find every station that connects to this point and sever the connection*/
	for (int j = 0; j < StationsCounter; j++) {//iterate through every Station
		for (int i = 0; i < Stations[j]->GetAccessNumbers().y; i++) {//Iterate through the Exits
			if (Stations[j]->GetNextPoint(i) == Point) {//if it matches the point that we want
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
	Vector2D<float> CoordsA = PointA->GetTransformComponent()->GetPosition() / GAME_OBJECT_HEIGHT;
	Vector2D<float> CoordsB = PointB->GetTransformComponent()->GetPosition() / GAME_OBJECT_HEIGHT;
	Vector2D<float> Direction = CoordsB - CoordsA;
	int TrackCoordinate{};

	if (Direction.x != 0) {
		for (int i = 1; i < abs(Direction.x); i++) {
			TrackCoordinate = CoordsA.x + Direction.x / abs(Direction.x) * i;
			GameMap[(int)CoordsA.y][TrackCoordinate] = TileTypes::TrackVertical;

		}
	}
	else if (Direction.y != 0) {
		for (int i = 1; i < abs(Direction.y); i++) {
			TrackCoordinate = CoordsA.y + Direction.y / abs(Direction.y) * i;
			GameMap[TrackCoordinate][(int)CoordsA.x] = TileTypes::TrackHorizontal;
		}
	}

}

void Game::HandleHitsUnderCursor() {
	/*Get the coordinates of the click*/
	int x, y;
	bool CanSwapLine{ true };
	double DistanceToCursor{};
	SDL_GetMouseState(&x, &y);
	//std::cout << "Clicked Left mouse button at tile coordinates " << x << "," << y << std::endl;

	/*Check for train hit*/
	for (int i = 0; i < TrainsCounter; i++) {
		for (int j = 0; j < NUMBER_OF_CARS; j++) {
			DistanceToCursor = (Trains[i]->GetCar(j)->GetTransformComponent()->GetPosition() - Vector2D<float>{ float(x - TILE_WIDTH / 2), float( y - TILE_HEIGHT / 2) }).Abs();
			if (DistanceToCursor <= TILE_HEIGHT / 2) {
				std::cout << "Distance to cursor = " << DistanceToCursor << std::endl;
				Trains[i]->SetIsMoving(!Trains[i]->GetIsMoving());
			}
		}
	}
	/*Check for station hit and handle line swapping*/
	for (int i = 0; i < StationsCounter; i++) {
		if ((Stations[i]->GetTransformComponent()->GetPosition() - Vector2D<float>{float(x - TILE_WIDTH / 2), float(y - TILE_HEIGHT / 2)}).Abs() <= TILE_HEIGHT / 2) {
			for (int k = 0; k < TrainsCounter; k++) {//check if any train is at the station
				for (int j = 0; j < NUMBER_OF_CARS; j++) {//check per car
					if ((Trains[k]->GetCar(j)->GetTransformComponent()->GetPosition() - Stations[i]->GetTransformComponent()->GetPosition()).Abs() <= TILE_HEIGHT / 2) {
						CanSwapLine = false;// if there is a car at the station we must not swap lines
					}
				}
			}
			if (!Stations[i]->GetIsTrainInStation())//No cars at the station means we can swap lines
				Stations[i]->SwapNextPoint(Stations[i]->GetNextPoint(1), Stations[i]->GetNextPoint(1));

		}

	}

	/*Switch the Signal Lights between green and red*/

	for (int i = 0; i < SignalsCounter; i++) {
		if ((TrafficSignals[i]->GetTransformComponent()->GetPosition() - Vector2D<float>{float(x - TILE_WIDTH / 2), float(y - TILE_HEIGHT / 2) } ).Abs() <= TILE_HEIGHT / 2){
			TrafficSignals[i]->SetGreenLight(!TrafficSignals[i]->GetGreenLight());
		}
	}
	/*...Other types*/

	/*Nothing was clicked*/
}

bool Game::IsTrainInStation(RailwayPoint* Station) {
		for (int j = 0; j < TrainsCounter; j++) {
			for (int k = 0; k < NUMBER_OF_CARS; k++) {
				if ((Station->GetTransformComponent()->GetPosition() - Trains[j]->GetCar(k)->GetTransformComponent()->GetPosition()).Abs() < GAME_OBJECT_HEIGHT) {
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

RailwaySignal* Game::NewSignal(Vector2D<float> Position, Vector2D<float> TargetPosition, bool GreenLight)
{
	SignalsCounter++;
	Position = TileToPixelCoordinates(Position);
	TargetPosition = TileToPixelCoordinates(TargetPosition);

	return new RailwaySignal(Renderer, TransformComponent{ Position, Vector2D<float>{0,0}, 0.f }, TargetPosition, GreenLight);
}

void Game::DeleteSignal(RailwaySignal* Signal) {
	SignalsCounter--;
	delete(Signal);

}
