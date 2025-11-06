#pragma once
#include <SDL.h>
#include "Library.h"

class TileMap {
public:
	static constexpr int MapWidth = GAME_WINDOW_WIDTH / TILE_WIDTH;
	static constexpr int MapHeight = GAME_WINDOW_HEIGHT / TILE_HEIGHT;

	TileMap(SDL_Renderer* InRenderer, TileTypes TileData[MapHeight][MapWidth]);
	TileMap(SDL_Renderer* InRenderer);

	/*Draws the Map...*/
	void Draw();

	// Set all tiles from a tile type array
	void SetTiles(TileTypes MapData[MapHeight][MapWidth]);

	// Set a particular tile
	void SetTile(TileTypes TileType, Vector2D<int> TileCoordinate);

private:
	TileTypes Tiles[MapHeight][MapWidth];
	SDL_Renderer* Renderer{};
	SDL_Texture* Dirt{};
	SDL_Texture* Grass{};
	SDL_Texture* Water{};
	SDL_Texture* Track{};
};
