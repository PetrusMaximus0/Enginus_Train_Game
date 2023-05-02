#pragma once

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define GAME_WINDOW_WIDTH 1376
#define GAME_WINDOW_HEIGHT 768

template <class Type>
struct Vector2D {
	Type x{};
	Type y{};
};

enum class TileTypes : unsigned char
{
	Grass,
	Water,
	Dirt

};

