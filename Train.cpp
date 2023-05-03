#pragma once
#include "Train.h"
#include <iostream>
#include "TextureManager.h"



Train::Train(SDL_Renderer* InRenderer, Vector2D<int> InCoordinate, bool InIsMoving, int InCarSize, const char* InIdentifier) :
	IsMoving(InIsMoving), CarSize(InCarSize) {
	/*InitialCoordinates*/
	InitializeTrainCoordinates(InCoordinate);
	/*Identifier Initialization*/
	if (sizeof(InIdentifier) == 8) {
		Identifier[0] = InIdentifier[0];
		Identifier[1] = InIdentifier[1];

	}
}
void Train::Update() {
	


}

void Train::Render()
{


}

void Train::InitializeTrainCoordinates(Vector2D<int> InCoordinate) {
	for (int i = 0; i < 4; i++) {
		Coordinate[i].x = InCoordinate.x;
		Coordinate[i].y = InCoordinate.y;
	}

}

void Train::SetWagonTexture(GACarColor NewColor, int WagonID) {
	if (WagonID > 0 && WagonID < 3) {
		switch (NewColor) {
		case(GACarColor::Empty):
			TextureManager::LoadTexture(Renderer, "assets/art/car_empty_01.png");
			break;

		case(GACarColor::Blue):
			TextureManager::LoadTexture(Renderer, "assets/art/car_blue_01.png");
			break;

		case(GACarColor::Green):
			TextureManager::LoadTexture(Renderer, "assets/art/car_green_01.png");
			break;

		case(GACarColor::Orange):
			TextureManager::LoadTexture(Renderer, "assets/art/car_orange_01.png");
			break;

		case(GACarColor::Purple):
			TextureManager::LoadTexture(Renderer, "assets/art/car_purple_01.png");
			break;

		default:
			break;
		}
	}
}
/**Sets a new position for the locomotive and new position for the remainder of the cars on the train*/
void Train::MoveTrain(Vector2D<int> NewCoordinates) {
	for (int i = 3; i > 0; i--) {
		Coordinate[i].x = Coordinate[i - 1].x;
		Coordinate[i].y = Coordinate[i - 1].y;
	}
	Coordinate[0].x = NewCoordinates.x;
	Coordinate[0].y = NewCoordinates.y;
}

void Train::SetIsMoving(bool Moving) {
	IsMoving = Moving;
}

bool Train::GetIsMoving() { return Train::IsMoving; }
/**Returns the coordinates for the locomotive*/
Vector2D<int> Train::GetCoordinates() {
	return Coordinate[0];
}
/*Prints the identifier of the train, whether it is moving or not, the colour and coordinate of every wagon*/
void Train::PrintTrainDetails(bool OnlyCoordinates) {
	std::cout << Identifier[0] << Identifier[1] << " Locomotive is moving: " << GetIsMoving() << std::endl;
	if (!OnlyCoordinates) {

	}
}