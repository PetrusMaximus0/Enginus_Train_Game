#pragma once

#include "GameObject.h"
#include "RailwayPoint.h"

constexpr int NUMBER_OF_CARS{ 4 };

class Train
{
private:
	bool IsMoving{};
	char Identifier[3]{};
	GameObject* Cars[NUMBER_OF_CARS]{};
	ColorType CarColorType[NUMBER_OF_CARS]{};
	RailwayPoint* Destinations[NUMBER_OF_CARS]{};
	RailwayPoint* StartingStation{};
	bool IsActive{true};
	int MaxTrips{};
	int TripsCompleted{};
	bool WinConditon{};
	bool WaitingForSpawn{};
	float RemainingStopTime{};
	SDL_Renderer* Renderer{};

	void StopTrain();

public:
	Train(SDL_Renderer* InRenderer, bool InIsMoving, const char* InIdentifier, RailwayPoint* InitialStation, int InMaxTrips = 10);

	void SetCarColorType(ColorType NewColor, int CarID);

	~Train();

	void Update(float DeltaTime);

	void Render();

	void UpdateCars(float DeltaTime);

	void SetDestination(RailwayPoint* NewDestination, int CarID);

	void HandleCarStationInteraction();

	GameObject* GetCar(int Index);

	void SetIsMoving(bool Value);

	bool GetIsMoving();

	void Respawn();

	void MarkForDeletion();

	bool GetIsActive();

	void CheckWinCondition();

	void DeSpawn();

	void TemporaryStop(float time);
};

