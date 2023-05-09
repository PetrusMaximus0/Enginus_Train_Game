#pragma once
#include "GameObject.h"
#define MAX_CONNECTIONS_BETWEENPOINTS 2

class RailwayPoint : public GameObject
{
private:
	char Identifier[3]{};
	char Type[4]{};//station STA or waypoint WPT
	RailwayPoint* NextPoints[MAX_CONNECTIONS_BETWEENPOINTS]{};
	bool IsTrainInStation{};

protected:
	int NumberOfEntries{};
	int NumberOfExits{};
	

public:
	RailwayPoint(SDL_Renderer* InRenderer, Vector2D<int> InCoordinates, const char* InIdentifier, const char* InType);
	~RailwayPoint();
	void SetNextPoint(RailwayPoint* NextPoint);
	/*Clears pointer Point in the NextPoints Array, swaps last element of array 
	with the place of the deleted element*/
	void ClearNextPoint(RailwayPoint* Point, int PointID);
	void Update() override;
	void Render() override;
	RailwayPoint* GetNextPoint(int PointID = 0);
	/*the value in X is the Number of Entries and the value in Y is the number of exits*/
	Vector2D<int> GetAccessNumbers();
	void SetPointColorType(GACarColor NewColor);
	const char* GetIdentifier();
	void SwapNextPoint(RailwayPoint* NewNextPoint, RailwayPoint* NextPoint);
	void SetTrainInStation(bool Value);
	bool GetIsTrainInStation();

};

