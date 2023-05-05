#pragma once

#include "Train.h"
#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>

Train::Train(SDL_Renderer* InRenderer, bool InIsMoving, const char* InIdentifier, RailwayPoint* InitialStation, int InMaxTrips):
	Renderer(InRenderer),
	IsMoving(InIsMoving),
	MaxTrips(InMaxTrips)

{
	/*Create the cars and set their texture randomnly*/
	for (int i = 0; i < NUMBER_OF_CARS; i++) {	
		GACarColor Color = (GACarColor)(rand() % 4);//change 4 to number of colors
		Cars[i] = new GameObject(Renderer, InitialStation->GetPosition(), Color);
		Cars[i]->SetTexture(SetWagonTexture(Color, i));
		SetDestination(InitialStation->GetNextPoint(), i);
	}
	StartingStation = InitialStation;
	TripsCompleted = 0;
}

Train::~Train()
{
	for (int i = 0; i < NUMBER_OF_CARS; i++)
		delete(Cars[i]);
}

SDL_Texture* Train::SetWagonTexture(GACarColor NewColor, int WagonID)
{
	if (WagonID < NUMBER_OF_CARS) {
		SDL_Texture* Texture{};

		switch (NewColor) {
		case(GACarColor::Blue):
			Texture = TextureManager::LoadTexture(Renderer, "assets/art/car_blue_01.png");
			break;

		case(GACarColor::Green):
			Texture = TextureManager::LoadTexture(Renderer, "assets/art/car_green_01.png");
			break;

		case(GACarColor::Orange):
			Texture = TextureManager::LoadTexture(Renderer, "assets/art/car_orange_01.png");
			break;

		case(GACarColor::Purple):
			Texture = TextureManager::LoadTexture(Renderer, "assets/art/car_purple_01.png");
			break;

		case(GACarColor::Empty):
			Texture = TextureManager::LoadTexture(Renderer, "assets/art/car_empty_01.png");
			break;

		default:
			Texture = TextureManager::LoadTexture(Renderer, "assets/art/car_empty_01.png");
			break;
		}
		return Texture;
	}
}

void Train::SetColorType(GACarColor NewColor, int CarID)
{
	Cars[CarID]->SetColorType(NewColor);

	switch (NewColor) {
	case(GACarColor::Blue):
		Cars[CarID]->SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/car_blue_01.png"));
		break;

	case(GACarColor::Green):

		Cars[CarID]->SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/car_green_01.png"));
		break;

	case(GACarColor::Orange):
		Cars[CarID]->SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/car_orange_01.png"));
		break;

	case(GACarColor::Purple):
		Cars[CarID]->SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/car_purple_01.png"));
		break;

	case(GACarColor::Empty):
		Cars[CarID]->SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/car_empty_01.png"));
		break;
	}
}

void Train::Update()
{
	/*Verify possible Collisions*/
	//TBA

	/*Update the velocity of the Cars based on Station Presence*/
	if (IsMoving && Destinations[0]!=nullptr) {//need a check for this next point otherwise can cause access to nullptr
		HandleCarStationInteraction();// Handle car - station Interactions
		UpdateCars();
	}
	else {

	
	}
	
}

void Train::Render()
{
/*Render Cars one by one*/
	for (int i = 0; i < NUMBER_OF_CARS; i++) {
		Cars[i]->Render();
	}
} 

void Train::UpdateCars() {
	Vector2D<int> NewCoordinates{};
	/*Update Cars Position one by one*/
	for (int i = 1; i < NUMBER_OF_CARS; i++) {
		/*Find the correct Velocities*/
		Velocity[i] = (Destinations[i]->GetPosition() - Cars[i]->GetPosition()).Normalize();
		/*If The distance to the car in front is equal to the speed then the cars should move*/
		int Distance = (Cars[i - 1]->GetPosition() - Cars[i]->GetPosition()).ManhatanAbs();
		if (Distance >= GAME_OBJECT_WIDTH)
			Cars[i]->SetTransform(Cars[i]->GetPosition() + Velocity[i]);
		Cars[i]->Update();
	}
	//Update the locomotive Position
	Velocity[0] = (Destinations[0]->GetPosition() - Cars[0]->GetPosition()).Normalize();
	/*If the locomotive hasnt reached the destination*/
	if ((Destinations[0]->GetPosition() - Cars[0]->GetPosition()).ManhatanAbs() > 0) {
		NewCoordinates = Cars[0]->GetPosition() + Velocity[0];// keep it moving
		Cars[0]->SetTransform(NewCoordinates);

	}
	Cars[0]->Update();


}

void Train::SetDestination(RailwayPoint* NewDestination, int CarID){
	Destinations[CarID] = NewDestination;
}

void Train::HandleCarStationInteraction() {
	int Distance{};

	for (int i = 0; i < NUMBER_OF_CARS; i++) {
		Distance = (Destinations[i]->GetPosition() - Cars[i]->GetPosition()).ManhatanAbs();
		if (Distance == 0) {
			//empty the car
			if (Cars[i]->GetColorType() == Destinations[i]->GetColorType()) {
				SetColorType(GACarColor::Empty, i);
			}
			//set a new destination or stops the train if there isn't one
			if (Destinations[i]->GetAccessNumbers().y > 0) {
				SetDestination(Destinations[i]->GetNextPoint(), i);
			
			}else if (TripsCompleted < MaxTrips && !WinConditon) {
				Respawn();
				TripsCompleted++;
				break;

			}else {
				MarkForDeletion();
			}
		}
	}
}

GameObject* Train::GetCar(int Index)
{
	return Cars[Index];
}

void Train::SetIsMoving(bool Value) { Train::IsMoving = Value; }

bool Train::GetIsMoving() { return IsMoving; }

void Train::StopTrain() {
	for (int i = 0; i < NUMBER_OF_CARS; i++) {
		Velocity[i] = Vector2D<int>{ 0,0 };
	}
}

void Train::Respawn() {
	for (int i = 0; i < NUMBER_OF_CARS; i++){
		Cars[i]->SetTransform(StartingStation->GetPosition());
		SetDestination(StartingStation, i);
	}

}

void Train::MarkForDeletion() {
	IsActive = false;
}

bool Train::GetIsActive() { return IsActive;}

void Train::CheckWinCondition() {
	int  k = 0;
	while (k < NUMBER_OF_CARS) {
		if (Cars[k]->GetColorType() != GACarColor::Empty)
			break;
		k++;
	}
	if (k == NUMBER_OF_CARS)
		WinConditon = true;
}
