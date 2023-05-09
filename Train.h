#pragma once

#include "GameObject.h"
#include "Library.h"
#include "RailwayPoint.h"

#define NUMBER_OF_CARS 5

class Train
{
private:
	bool IsMoving{};
	char Identifier[3]{};
	GameObject* Cars[NUMBER_OF_CARS];
	SDL_Renderer* Renderer{};
	Vector2D<int> Velocity[NUMBER_OF_CARS]{};
	RailwayPoint* Destinations[NUMBER_OF_CARS]{};
	RailwayPoint* StartingStation{};
	bool IsActive{true};
	int MaxTrips{};
	int TripsCompleted{};
	bool WinConditon{};
	bool WaitingForSpawn{};
	float RemainingStopTime{};
	
public:
	Train(SDL_Renderer* InRenderer, bool InIsMoving, const char* InIdentifier, RailwayPoint* InitialStation, int InMaxTrips = 10);

	void SetCarColorType(GACarColor NewColor, int CarID);

	~Train();

	void Update();

	void Render();

	void UpdateCars();

	void SetDestination(RailwayPoint* NewDestination, int CarID);

	void HandleCarStationInteraction();

	GameObject* GetCar(int Index);

	void SetIsMoving(bool Value);

	bool GetIsMoving();

	void StopTrain();

	void Respawn();

	void MarkForDeletion();

	bool GetIsActive();

	void CheckWinCondition();
	void DeSpawn();
};

