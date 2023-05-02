#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include "Library.h"

class Game{
public:
	Game();
	~Game();
	void Init(const char* title, int PositionX, int PositionY, int Width, int Height, bool IsFullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool GetIsRunning();
	void AddTile(int TileId, Vector2D<int> Coordinates);
	

private:
	SDL_Renderer* Renderer{};
	bool IsRunning{};
	SDL_Window* Window{};
	int UpdateCounter{};
};
