#include "Game.h"
#include "Library.h"
#include "TextureManager.h"

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