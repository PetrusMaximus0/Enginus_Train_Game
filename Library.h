#pragma once

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define GAME_WINDOW_WIDTH 1376
#define GAME_WINDOW_HEIGHT 768

template <class Type>
struct Vector2D {
	Type x{};
	Type y{};

	int ManhatanAbs() {
		return (int)(abs(x) + abs(y));
	}
	/*Returns the int type vector2d with the non zero component with absolute value of one*/
	Vector2D<int> Normalize() {
		if (x != 0)
			x = x / abs(x);
		if (y != 0)
			y = y / abs(y);
		
		return Vector2D<int>{x, y};
	}

	Vector2D operator + (const Vector2D& other) const {

		Vector2D result;

		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	Vector2D operator - (const Vector2D& other) const {

		Vector2D result;

		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	Vector2D operator * (const int other) const {
	
		Vector2D result;
		result.x = x * other;
		result.y = y * other;

		return result;
	
	}

	Vector2D operator / (const int other) const {

		Vector2D result;
		result.x = x / other;
		result.y = y / other;

		return result;

	}

};

enum class TileTypes : unsigned char
{
	Grass,
	Water,
	Dirt,
	TrackVertical,
	TrackHorizontal

};

enum class GACarColor : unsigned char {
	Blue,
	Green,
	Orange,
	Purple,
	Empty
};


