#include "Map.h"
#include "TextureManager.h"


Map::Map(SDL_Renderer* InRenderer): 
	Renderer(InRenderer),
	Dirt(TextureManager::LoadTexture(Renderer, "assets//art//tile_dirt_01.png")),
	Water(TextureManager::LoadTexture(Renderer, "assets//art//tile_water_01.png")),
	Grass(TextureManager::LoadTexture(Renderer, "assets//art//tile_grass_01.png"))

{
	std::srand((unsigned)time(nullptr));
	int RandomNumber{};

	/*TEMPORARY - MAP*/
	//Populated with zeroes.
	TileTypes level1[MapWidth][MapHeight];
	LoadMap(level1);

	SourceRectangle.x = 0;
	SourceRectangle.y = 0;
	SourceRectangle.w = TILE_WIDTH;
	SourceRectangle.h = TILE_HEIGHT;
	
	DestinationRectangle.x = 0;
	DestinationRectangle.y = 0;
	DestinationRectangle.w = TILE_WIDTH;
	DestinationRectangle.h = TILE_HEIGHT;
	/*END TEMPORARY*/
}	

Map::~Map()
{
}

void Map::LoadMap(TileTypes MapArray[MapWidth][MapHeight])
{
	for (int row = 0; row < MapHeight; row++) {
		for (int column = 0; column < MapWidth; column++) {
			//Use this one
			//MapData[row][column] = MapArray[row][column];
			
			//Random tiles
			MapData[row][column] = (TileTypes)(rand() % 3);
		}
	}


}

void Map::DrawMap()
{
	TileTypes TempTile{};

	for (int row = 0; row < MapHeight; row++) {
		for (int column = 0; column < MapWidth; column++) {
			TempTile = MapData[row][column];
			//SETTING THE DESTINATION IN THE CORRECT PIXEL COORDINATE
			//as every tile has size height x width
			DestinationRectangle.x = column * TILE_HEIGHT;
			DestinationRectangle.y = row * TILE_WIDTH;

			switch (TempTile){
			
			case TileTypes::Water:
				TextureManager::Draw(Renderer, Water, SourceRectangle, DestinationRectangle);
				//std::cout << "Loaded Water texture \n";
				break;
				
			case TileTypes::Dirt:
				TextureManager::Draw(Renderer, Dirt, SourceRectangle, DestinationRectangle);
				//std::cout << "Loaded Dirt texture \n";
				break;
				
			case TileTypes::Grass:
				TextureManager::Draw(Renderer, Grass, SourceRectangle, DestinationRectangle);
				//std::cout << "Loaded Grass texture \n";
				break;
				
			default:
				std::cout << "ERROR, unknown texture selected" << std::endl;
				break;
			}
			

		}
	}



}
