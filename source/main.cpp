#include "Game.h"
#include "Library.h"
#include "TextureManager.h"
#include <iostream>

int main(int argc, char* args[]) {

	std::srand((unsigned)time(nullptr));
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	
	/*FRAME RATE LIMITING*/
	const int FramesPerSecond{ 60 };
	const int FrameDelay{ 1000 / FramesPerSecond };
	Uint32 FrameStart{ 0 };
	int FrameTime{ 0 };

	/*INITIALIZE A GAME INSTANCE*/
	Game* OGame{};
	OGame = new Game("Enginus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, false, FramesPerSecond);
	
	/*MAIN GAME LOOP*/
	while (OGame->GetIsRunning()) {
		//Get a delta time for the update
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
		
		//Get the time at which the frame started
		FrameStart = SDL_GetTicks();

		OGame->HandleEvents();
		OGame->Update(1);
		OGame->Render();
		
		//delay frame in case of 
		FrameTime = SDL_GetTicks() - FrameStart;
		if (FrameDelay > FrameTime)
			SDL_Delay(FrameDelay - FrameTime);
	}

	/*CLEAN UP*/
	OGame->Clean();
	delete OGame;

	return 0;
}  