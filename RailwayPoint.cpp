#pragma once
#include "RailwayPoint.h"
#include <SDL.h>
#include <iostream>
#include "TextureManager.h"

RailwayPoint::RailwayPoint(SDL_Renderer* InRenderer, const char* TextureSheet, Vector2D<int> InCoordinates, const char* InIdentifier, const char* InType) :
	GameObject(InRenderer, TextureSheet, InCoordinates)
{	strncpy_s(Identifier, InIdentifier, sizeof(Identifier));
	strncpy_s(Type, InType, sizeof(Type));

	/*Set a random colored texture if the point is a station and set the waypoint texture otherwise*/
	if (!strncmp("WPT", Type, sizeof("WPT"))) {
		GACarColor NewColorType = (GACarColor)(rand() % 4);
		SetPointColorType(NewColorType);
	}
	else {
		SetPointColorType(GACarColor::Empty);
	
	}

}

RailwayPoint::~RailwayPoint()
{


}

void RailwayPoint::InitializePoint()
{

}

void RailwayPoint::SetNextPoint(RailwayPoint* NextPoint)
{
	if (NumberOfExits < MAX_CONNECTIONS_BETWEENPOINTS && NextPoint->NumberOfEntries < MAX_CONNECTIONS_BETWEENPOINTS) {
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

void RailwayPoint::Update()
{
	GameObject::Update();
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
			SDL_RenderDrawLine(Renderer, Coordinates.x + GAME_OBJECT_WIDTH / 2, Coordinates.y + GAME_OBJECT_HEIGHT / 2, NextPoints[i]->Coordinates.x + GAME_OBJECT_WIDTH / 2, NextPoints[i]->Coordinates.y + GAME_OBJECT_HEIGHT / 2);
		}
	}

}

RailwayPoint* RailwayPoint::GetNextPoint(int PointID)
{
	return NextPoints[PointID];
}

Vector2D<int> RailwayPoint::GetAccessNumbers()
{
	return Vector2D<int>{NumberOfEntries, NumberOfExits};
}

void RailwayPoint::SetPointColorType(GACarColor NewColor)
{
	ColorType = NewColor;
	switch (NewColor) {
		case(GACarColor::Blue):
			SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/station_blue_01.png"));
			break;

		case(GACarColor::Green):

			SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/station_green_01.png"));
			break;

		case(GACarColor::Orange):
			SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/station_orange_01.png"));
			break;

		case(GACarColor::Purple):
			SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/station_purple_01.png"));
			break;

		case(GACarColor::Empty):
			SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/waypoint_01.png"));
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
