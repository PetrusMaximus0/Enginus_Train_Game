#pragma once
#include "GameObject.h"
#include "Library.h"

constexpr int MAX_CONNECTIONS_BETWEEN_POINTS{ 2 };

class RailwayPoint : public GameObject
{
private:
	char Identifier[3]{};
	char Type[4]{};//station STA or waypoint WPT
	ColorType StationColor{};
	RailwayPoint* NextPoints[MAX_CONNECTIONS_BETWEEN_POINTS]{};

	bool IsTrainInStation{};

protected:
	int NumberOfEntries{};
	int NumberOfExits{};
	
public:
	RailwayPoint(SDL_Renderer* InRenderer, TransformComponent InTransform, const char* InIdentifier, const char* InType, ColorType = ColorType::Empty);
	~RailwayPoint();

	void SetNextPoint(RailwayPoint* NextPoint);
	/*Clears pointer Point in the NextPoints Array, swaps last element of array 
	with the place of the deleted element*/
	void ClearNextPoint(RailwayPoint* Point, int PointID);
	void Update(float DeltaTime) override;
	void Render() override;
	RailwayPoint* GetNextPoint(int PointID = 0);
	/*the value in X is the Number of Entries and the value in Y is the number of exits*/
	Vector2D<int> GetAccessNumbers();
	void SetPointColorType(ColorType NewColor);
	const char* GetIdentifier();
	void SwapNextPoint(RailwayPoint* NewNextPoint, RailwayPoint* NextPoint);
	void SetTrainInStation(bool Value);
	bool GetIsTrainInStation();
	ColorType GetColorType();

};

