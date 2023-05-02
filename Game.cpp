#pragma once
#include "Game.h"
//#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
//#include "EntityComponentSystem.h"
#include "Components.h"
//#include "Library.h"
// 
//TEMPORARY GLOBALS
GameObject* Train{};
GameObject* Train2{};
Map* GameWorld{};
Manager GameManager;
auto& Train3(GameManager.AddEntity());

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
	//Creation of Textures.
	Vector2D <int>Vector{ 500,500 };
	Vector2D <int>Vector2{ 100, 100 };
	//Spawn a new Train
	Train = new GameObject(Renderer,"assets//art//car_blue_01.png", Vector);
	Train2 = new GameObject(Renderer,"assets//art//tile_track_basic_01.png", Vector2);
	GameWorld = new Map(Renderer);
	Train3.AddComponent<PositionComponent>();
	Train3.GetComponent<PositionComponent>().SetPos(100,100);
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
	Train->Update();
	Train2->Update();
	GameManager.Update();
	std::cout << Train3.GetComponent<PositionComponent>().GetPosition().x << "," 
		      << Train3.GetComponent<PositionComponent>().GetPosition().y << std::endl;
	//update the rectangle position and drawing size
	//std::cout << UpdateCounter << std::endl;

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
	//Foreground Objects
	Train->Render();
	Train2->Render();
	//present the new stuff on screen
	SDL_RenderPresent(Renderer);
}

void Game::Clean()
{
	/*Performs cleanup of SDL before calling SDL_Quit()*/
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	delete Train;
	delete Train2;
	delete GameWorld;
	std::cout << "Game cleaning complete" << std::endl;
}

bool Game::GetIsRunning(){return IsRunning;}

void Game::AddTile(int TileId, Vector2D<int> Coordinates) {


}