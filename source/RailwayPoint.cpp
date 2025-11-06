#include "RailwayPoint.h"

#include <iostream>
#include <cstring>

#include "SpriteComponent.h"
#include "TransformComponent.h"

RailwayPoint::RailwayPoint(SDL_Renderer* InRenderer, TransformComponent InTransform, const char* InIdentifier, const char* InType, ColorType Color) :
	GameObject(InRenderer, InTransform)
{	
	/*Set the ID and the Type of Point*/
	std::strncpy(Identifier, InIdentifier, sizeof(Identifier)-1);
	std::strncpy(Type, InType, sizeof(Type)-1);

	/*Randomize the color of the station and assign color empty if not a station*/
	if (!strncmp("STA", Type, sizeof("STA"))) {
		ColorType NewColorType = (ColorType)(rand() % 4);
		SetPointColorType(NewColorType);
	}
	else {
		SetPointColorType(ColorType::Empty);
	}
}

RailwayPoint::~RailwayPoint()
{


}

void RailwayPoint::SetNextPoint(RailwayPoint* NextPoint)
{
	if (NumberOfExits < MAX_CONNECTIONS_BETWEEN_POINTS && NextPoint->NumberOfEntries < MAX_CONNECTIONS_BETWEEN_POINTS) {
		NextPoints[NumberOfExits] = NextPoint;
		NumberOfExits += 1;
		NextPoint->NumberOfEntries += 1;
	}
}

void RailwayPoint::ClearNextPoint(RailwayPoint* Point, int ID)
{
	if (NextPoints[ID] == Point) {
		Point->NumberOfEntries--;
		NumberOfExits--;

		if (ID != NumberOfExits - 1) {//if its not the last element of the array
			NextPoints[ID] = NextPoints[NumberOfExits-1]; // swap the last for the one deleted
			NextPoints[NumberOfExits - 1] = nullptr;//clear the last element

		}else{//it is the last element and can be cleared normally
			NextPoints[ID] = nullptr;
		}
		
	}
}

void RailwayPoint::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void RailwayPoint::Render()
{
	GameObject::Render();
	for (int i = 0; i < NumberOfExits; i++) {
		
		if (NextPoints[i]){
			if (i == 0) {
				SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);//GREEN
			}
			else {
				SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);//RED
			}
			SDL_RenderDrawLine(Renderer, TransformComp->GetPosition().x + GAME_OBJECT_WIDTH / 2, TransformComp->GetPosition().y + GAME_OBJECT_HEIGHT / 2, NextPoints[i]->TransformComp->GetPosition().x + GAME_OBJECT_WIDTH / 2, NextPoints[i]->TransformComp->GetPosition().y + GAME_OBJECT_HEIGHT / 2);
		}
	}

}

RailwayPoint* RailwayPoint::GetNextPoint(int PointID) {	return NextPoints[PointID]; }

Vector2D<int> RailwayPoint::GetAccessNumbers()
{
	return Vector2D<int>{NumberOfEntries, NumberOfExits};
}

void RailwayPoint::SetPointColorType(ColorType NewColor)
{
	StationColor = NewColor;
	switch (NewColor) {
		case(ColorType::Blue):
			SpriteComp->SetTexture("assets/art/station_blue_01.png");
			break;

		case(ColorType::Green):
			SpriteComp->SetTexture("assets/art/station_green_01.png");
			break;

		case(ColorType::Orange):
			SpriteComp->SetTexture("assets/art/station_orange_01.png");
			break;

		case(ColorType::Purple):
			SpriteComp->SetTexture("assets/art/station_purple_01.png");
			break;

		case(ColorType::Empty):
			SpriteComp->SetTexture("assets/art/waypoint_01.png");
			break;
	}
}

const char* RailwayPoint::GetIdentifier()
{
	return Identifier;
}

void RailwayPoint::SwapNextPoint(RailwayPoint* NewNextPoint, RailwayPoint* NextPoint)
{
	RailwayPoint* TempPoint{};
	int NewNextPointIndex{};
	if (!IsTrainInStation) {
		/*Finds the index of the new next point*/
		for (int i = 0; i < NumberOfExits; i++) {
			if (NextPoints[i] == NewNextPoint) {
				NewNextPointIndex = i;
				break;
			}
		}
		if (NewNextPointIndex != 0)
		{
			//Swap the array entries
			TempPoint = NextPoints[0];
			NextPoints[0] = NewNextPoint;
			NextPoints[NewNextPointIndex] = TempPoint;

		}
	}
	

}

void RailwayPoint::SetTrainInStation(bool Value)
{
	IsTrainInStation = Value;
}

bool RailwayPoint::GetIsTrainInStation(){return IsTrainInStation;}

ColorType RailwayPoint::GetColorType() { return StationColor; }
