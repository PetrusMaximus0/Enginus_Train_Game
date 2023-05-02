#include "Game.h"
#include "Library.h"

struct GAColor {
	int red{};
	int green{};
	int blue{};
	int alpha{};

};

struct RailwayPoint {
	char Identifier[4]{};
	int CoordinateX{};
	int CoordinateY{};
	char Type[3]{};//station STA or waypoint WPT
	int Size{};
	GAColor Color{};
	int NumberOfEntries{};
	int NumberOfExits{};

};

struct GACoordinates {
	int x{};
	int y{};
};

class Train {

private:
	bool IsMoving{};
	char Identifier[2]{};
	int CarSize{};
	GAColor CarColors[4]{};
	GACoordinates Coordinate[4]{};

public:
	Train(GAColor* InCarColors, GACoordinates InCoordinate, bool InIsMoving, int InCarSize, char* InIdentifier) {
		/*WagonColors*/
		for (int i = 0; i < 4; i++)
			ChangeWagonColors(InCarColors[i], i);
		/*InitialCoordinates*/
		InitializeTrainCoordinates(InCoordinate);
		/*Moving Flag*/
		IsMoving = InIsMoving;
		/*Car Sizes*/
		CarSize = InCarSize;
		/*Identifier Initialization*/
		if (sizeof(InIdentifier) == 8) {
			Identifier[0] = InIdentifier[0];
			Identifier[1] = InIdentifier[1];

		}
	}	

	void InitializeTrainCoordinates(GACoordinates InCoordinate) {
		for (int i = 0; i < 4; i++) {
			Coordinate[i].x = InCoordinate.x;
			Coordinate[i].y = InCoordinate.y;
		}


	}

	void ChangeWagonColors(GAColor NewColor, int WagonID) {
		if (WagonID > -1 && WagonID < 4) {
			CarColors[WagonID].alpha = NewColor.alpha;
			CarColors[WagonID].red = NewColor.red;
			CarColors[WagonID].green = NewColor.green;
			CarColors[WagonID].blue = NewColor.blue;

		}
	}
	/**Sets a new position for the locomotive and new position for the remainder of the cars on the train*/
	void MoveTrain(GACoordinates NewCoordinates) {
		for (int i = 3; i > 0 ; i--) {
			Coordinate[i].x = Coordinate[i - 1].x;
			Coordinate[i].y = Coordinate[i - 1].y;
		}
		Coordinate[0].x = NewCoordinates.x;
		Coordinate[0].y = NewCoordinates.y;
	}

	void SetIsMoving(bool Moving) {
		IsMoving = Moving;
	}

	bool GetIsMoving() { return IsMoving; }
	/**Returns the coordinates for the locomotive*/
	GACoordinates GetCoordinates() {
		return Coordinate[0];
	}
	/*Prints the identifier of the train, whether it is moving or not, the colour and coordinate of every wagon*/
	void PrintTrainDetails(bool OnlyCoordinates) {
		std::cout << Identifier[0] << Identifier[1] << " Locomotive is moving: " << GetIsMoving() << std::endl;
		if (!OnlyCoordinates) {
			for (int i = 0; i < 4; i++) {
				std::cout << " Wagon number " << i << " has the colors: " << CarColors[i].red << " " << CarColors[i].green << " " << CarColors[i].blue << " " << CarColors[i].alpha << std::endl;
				std::cout << "Wagon has Coordinates ( " << Coordinate[i].x << ", " << Coordinate[i].y << " )" << std::endl;
			}
		}		
	}

};

Game* OGame{};

int main(int argc, char* args[]) {

	/*FRAME RATE LIMITING*/
	const int FramesPerSecond{ 20 };
	const int FrameDelay{ 1000 / FramesPerSecond };
	Uint32 FrameStart{ 0 };
	int FrameTime{ 0 };
	/*INITIALIZE A GAME INSTANCE*/
	OGame = new Game();
	OGame->Init("Enginus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, false);
	
	/*MAIN GAME LOOP*/
	while (OGame->GetIsRunning()) {
		//Get the time at which the frame started
		FrameStart = SDL_GetTicks();

		OGame->HandleEvents();
		OGame->Update();
		OGame->Render();
		
		//delay frame in case of 
		FrameTime = SDL_GetTicks() - FrameStart;
		if (FrameDelay > FrameTime)
			SDL_Delay(FrameDelay - FrameTime);
		else
			std::cout << "Game is slower than frame rate delay\n";

	


	}

	OGame->Clean();
	delete OGame;

	return 0;
}  