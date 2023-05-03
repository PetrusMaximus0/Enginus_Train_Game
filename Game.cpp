#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"

// 
//TEMPORARY GLOBALS

Map* GameWorld{};
Manager GameManager;
//auto& Train(GameManager.AddEntity());
RailwayPoint* Stations[5]{};

Game::Game() {
	/*Default constructor for class Game*/
	IsRunning = false;

}

Game::~Game() {
	/*Default destructor for class Game*/
}

void Game::Init(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen)
{
	/*Initialize SDL, window and renderer. Initialize the Textures*/
	//full or windowed screen mode 
	int Flag{ 0 };
	IsFullscreen ? Flag = SDL_WINDOW_FULLSCREEN : false;
	
	//Initialize SDL window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized... " << std::endl;
		Window = SDL_CreateWindow(title, PositionX, PositionY, Width, Height, Flag);
		
		if (Window) {
			std::cout << "Window Created..." << std::endl;
			Renderer = SDL_CreateRenderer(Window, -1, 0);
			
			if (Renderer) {
				std::cout << "Renderer Created" << std::endl;
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				IsRunning = true;

			}
		}
	}
	//Spawn a new Train
	GameWorld = new Map(Renderer);

	InitializeTrains();
}

void Game::HandleEvents(){
	/*Handles SDL events such as SDL_QUIT and others ( TBA )*/
	
	SDL_Event Event{};
	SDL_PollEvent(&Event);
	
	switch (Event.type) {
	case SDL_QUIT:// in case of this event, the game is set to not running and thus the program will proceed to Game::Clean()
		IsRunning = false;
		break;
	default:
		break;

	}


}

void Game::Update()
{
	/*Updates the game state with new information */
	UpdateCounter++;
	GameManager.Update();

	for (auto& Stat : Stations) {Stat->Update();}


}

void Game::Render()
{
	/*Renders the game elements with the SDL library */
	
	//Clear old stuff
	SDL_RenderClear(Renderer);
	//add new stuff to render
	//Background Objects
	//GameWorld->LoadMap();//Used to Change Maps
	GameWorld->DrawMap();
	for (auto& Stat : Stations) { Stat->Render(); }
	GameManager.Draw();
	//Foreground Objects
	//present the new stuff on screen
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	/*Performs cleanup of SDL before calling SDL_Quit()*/
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	delete GameWorld;
	std::cout << "Game cleaning complete" << std::endl;
}

bool Game::GetIsRunning(){return IsRunning;}

void Game::AddTile(int TileId, Vector2D<int> Coordinates) {


}

void Game::InitializeTrains() {
	//Train.AddComponent<PositionComponent>(100, 100);
	//Train.AddComponent<SpriteComponent>(Renderer, "assets/art/car_purple_01.png");
	Stations[0] = new RailwayPoint(Renderer, "assets/art/car_purple_01.png", Vector2D<int>{50, 25});
	
};