#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
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
	static SDL_Renderer* Renderer;

private:
	bool IsRunning{};
	SDL_Window* Window{};
	int UpdateCounter{};
};
