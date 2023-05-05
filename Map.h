#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Library.h"

class Map {
public:
	Map(SDL_Renderer* InRenderer);
	~Map();
	static constexpr int MapWidth = GAME_WINDOW_WIDTH / TILE_WIDTH;
	static constexpr int MapHeight = GAME_WINDOW_HEIGHT / TILE_HEIGHT;
	/*Loads the Map....*/
	void LoadMap(TileTypes MapArray[MapHeight][MapWidth]);
	/*Draws the Map...*/
	void DrawMap();

private:
	SDL_Renderer* Renderer{};
	SDL_Rect SourceRectangle{}, DestinationRectangle{};
	SDL_Texture* Dirt{};
	SDL_Texture* Grass{};
	SDL_Texture* Water{};
	SDL_Texture* Track{};
	/*Map holds information on the map tiles*/
	TileTypes MapData[MapHeight][MapWidth]{};

};
