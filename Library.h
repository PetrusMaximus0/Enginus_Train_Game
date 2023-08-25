#pragma once

constexpr int TILE_WIDTH{ 32 };
constexpr int TILE_HEIGHT{ 32 };
constexpr int GAME_WINDOW_WIDTH{ 1376 };
constexpr int GAME_WINDOW_HEIGHT{ 768 };


template <class Type>
struct Vector2D {
	Type x{};
	Type y{};

	int ManhatanAbs() {
		return (int)(abs(x) + abs(y));
	}

	double Abs() {
		return sqrt(pow(x,2) + pow(y,2));
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

	Vector2D operator * (const Type other) const {
	
		Vector2D result;
		result.x = x * other;
		result.y = y * other;

		return result;
	
	}

	Vector2D operator / (const Type other) const {

		Vector2D result;
		result.x = x / other;
		result.y = y / other;

		return result;

	}

	bool operator == (const Vector2D<Type>& other) const {
		return other.x == x && other.y == y;
	}
	bool operator != (const Vector2D& other) const {
		return other.x != x || other.y != y;
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

template <class Type>
Vector2D<int> TileToPixelCoordinates(Vector2D<Type> Coordinates ) {
	Vector2D<int> TileCoordinates{};
	TileCoordinates.x = int(Coordinates.x * TILE_WIDTH);
	TileCoordinates.y = int(Coordinates.y * TILE_HEIGHT);
	return TileCoordinates;
}
