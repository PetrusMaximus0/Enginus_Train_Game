#pragma once

#include "Train.h"
#include "TextureManager.h"

Train::Train(SDL_Renderer* InRenderer, bool InIsMoving, const char* InIdentifier, RailwayPoint* InitialStation, int InMaxTrips):
	Renderer(InRenderer),
	IsMoving(InIsMoving),
	MaxTrips(InMaxTrips)

{
	/*Create the cars and set their texture randomnly*/
	for (int i = 0; i < NUMBER_OF_CARS; i++) {	
		ColorType Color = (ColorType)(rand() % 4);//change 4 to number of colors
		Cars[i] = new GameObject(Renderer, InitialStation->GetTransformComponent()->GetTransform());
		SetCarColorType(Color, i);
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

void Train::SetCarColorType(ColorType NewColor, int CarID)
{
	CarColorType[CarID] = NewColor;

	switch (NewColor) {
	case(ColorType::Blue):
		Cars[CarID]->GetSpriteComponent()->SetTexture("assets/art/car_blue_01.png");
		break;

	case(ColorType::Green):
		Cars[CarID]->GetSpriteComponent()->SetTexture("assets/art/car_green_01.png");
		break;

	case(ColorType::Orange):
		Cars[CarID]->GetSpriteComponent()->SetTexture("assets/art/car_orange_01.png");
		break;

	case(ColorType::Purple):
		Cars[CarID]->GetSpriteComponent()->SetTexture("assets/art/car_purple_01.png");
		break;

	case(ColorType::Empty):
		Cars[CarID]->GetSpriteComponent()->SetTexture("assets/art/car_empty_01.png");
		break;
	}
}

void Train::Update(float DeltaTime)
{
	/*Verify possible Collisions*/
	//TBA
	if (!WaitingForSpawn) {
		/*Update the velocity of the Cars based on Station Presence*/
		if (IsMoving && Destinations[0] != nullptr && RemainingStopTime == 0) {//need a check for this next point otherwise can cause access to nullptr
			HandleCarStationInteraction();// Handle car - station Interactions
			CheckWinCondition();
			UpdateCars(DeltaTime);
		}
		else if (RemainingStopTime > 0) {
			RemainingStopTime--;
			if (RemainingStopTime == 0)
				SetIsMoving(true);
		}
	
	}else{
		Respawn();
	}

	
}

void Train::Render()
{
/*Render Cars one by one*/
	if (!WaitingForSpawn)
		for (int i = 0; i < NUMBER_OF_CARS; i++)
			Cars[i]->Render();
} 

void Train::UpdateCars(float DeltaTime) {
	Vector2D<float> NewCoordinates{}, NewVelocity{};
	float Distance{}, SpeedMultiplier{ 1.f };
	TransformComponent* Transform{};
	
	/*Update Cars Position one by one*/
	for (int i = 1; i < NUMBER_OF_CARS; i++) {
		/*Find the correct Velocities*/
		Transform = Cars[i]->GetTransformComponent();
		
		/*If The distance to the car in front is equal to the speed then the cars should move*/
		Distance = (Cars[i - 1]->GetTransformComponent()->GetPosition() - Transform->GetPosition()).ManhatanAbs();
		if (Distance >= GAME_OBJECT_WIDTH) {
			NewVelocity = Destinations[i]->GetTransformComponent()->GetPosition() - Transform->GetPosition();
			NewVelocity = NewVelocity.Normalize() * SpeedMultiplier;
			Transform->SetVelocity(NewVelocity);

		}
		else{
			Transform->SetVelocity(Vector2D<float>{0,0});

		}		
		Cars[i]->Update(DeltaTime);

	}
	//Update the locomotive Position
	Transform = Cars[0]->GetTransformComponent();
	/*If the locomotive hasnt reached the destination*/
	Distance = (Destinations[0]->GetTransformComponent()->GetPosition() - Transform->GetPosition()).ManhatanAbs();
	if (Distance > 0) {
		NewVelocity = Destinations[0]->GetTransformComponent()->GetPosition() - Transform->GetPosition();
		NewVelocity = NewVelocity.Normalize() * SpeedMultiplier;
		Transform->SetVelocity(NewVelocity);

	}
	else {
		Transform->SetVelocity(Vector2D<float>{0, 0});

	}
	Cars[0]->Update(DeltaTime);


}

void Train::SetDestination(RailwayPoint* NewDestination, int CarID){
	Destinations[CarID] = NewDestination;
}

void Train::HandleCarStationInteraction() {
	double Distance{};
	for (int i = 0; i < NUMBER_OF_CARS; i++) {
		Distance = (Destinations[i]->GetTransformComponent()->GetPosition() - Cars[i]->GetTransformComponent()->GetPosition()).Abs();
		if ((int)Distance == 0) {
			if (CarColorType[i] != ColorType::Empty && CarColorType[i] == Destinations[i]->GetColorType()) {
				/*Empty the car*/
				SetCarColorType(ColorType::Empty, i);

				/*StopCars for a few seconds*/
				TemporaryStop(1.5 * 200);// x multiplies by frames per second
				
			}
			//set a new destination or stops the train if there isn't one
			if (Destinations[i]->GetAccessNumbers().y > 0) {
				SetDestination(Destinations[i]->GetNextPoint(), i);
			
			}else if (TripsCompleted < MaxTrips && !WinConditon) {
				DeSpawn();
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
		Cars[i]->GetTransformComponent()->SetVelocity(Vector2D<float>{0,0});
	}
}

void Train::Respawn() {
	
	if (!StartingStation->GetIsTrainInStation()) {
		for (int i = 0; i < NUMBER_OF_CARS; i++) {
			/*Resets the Position of the Cars to the initial spawn station*/
			Cars[i]->GetTransformComponent()->SetPosition(StartingStation->GetTransformComponent()->GetPosition());
			SetDestination(StartingStation, i);
			/*Changes the remaining colored cars's colors, so as to facilitate winning the game when there are no identical colored stations*/
			if (CarColorType[i] != ColorType::Empty)
				SetCarColorType((ColorType)(rand() % 4),i);
		}
		WaitingForSpawn = false;
		IsMoving = true;
	}
	


}

void Train::MarkForDeletion() {
	IsActive = false;
}

bool Train::GetIsActive() { return IsActive;}

void Train::CheckWinCondition() {
	int  k = 0;
	while (k < NUMBER_OF_CARS) {
		if (CarColorType[k] != ColorType::Empty)
			break;
		k++;
	}
	if (k == NUMBER_OF_CARS)
		WinConditon = true;
}

void Train::DeSpawn() {
	for (int i = 0; i < NUMBER_OF_CARS; i++)
		Cars[i]->GetTransformComponent()->SetPosition(Vector2D<float>{2000, 0});//send off screen
	WaitingForSpawn = true;
	IsMoving = false;

}

void Train::TemporaryStop(float time)
{
	RemainingStopTime = time;
	SetIsMoving(false);
}
