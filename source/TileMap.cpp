#include "TileMap.h"

#include "TextureManager.h"

TileMap::TileMap(SDL_Renderer *InRenderer, TileTypes TileData[MapHeight][MapWidth]) : Renderer(InRenderer),
    Dirt(TextureManager::LoadTexture(Renderer, "assets//art//tile_dirt_01.png")),
    Water(TextureManager::LoadTexture(Renderer, "assets//art//tile_water_01.png")),
    Grass(TextureManager::LoadTexture(Renderer, "assets//art//tile_grass_01.png")),
    Track(TextureManager::LoadTexture(Renderer, "assets//art//tile_track_basic_01.png")) {
    SetTiles(TileData);
}

TileMap::TileMap(SDL_Renderer *InRenderer) : Renderer(InRenderer),
                                             Dirt(TextureManager::LoadTexture(
                                                 Renderer, "assets//art//tile_dirt_01.png")),
                                             Water(TextureManager::LoadTexture(
                                                 Renderer, "assets//art//tile_water_01.png")),
                                             Grass(TextureManager::LoadTexture(
                                                 Renderer, "assets//art//tile_grass_01.png")),
                                             Track(TextureManager::LoadTexture(
                                                 Renderer, "assets//art//tile_track_basic_01.png")) {
    // Generate a default tilemap
    for (size_t row = 0; row < MapHeight; row++) {
        for (size_t column = 0; column < MapWidth; column++) {
            Tiles[row][column] = TileTypes::Water;
        }
    }
}

/*Set whole map*/
void TileMap::SetTiles(TileTypes Data[MapHeight][MapWidth]) {
    for (size_t row = 0; row < MapHeight; row++) {
        for (size_t column = 0; column < MapWidth; column++) {
            Tiles[row][column] = Data[row][column];
        }
    }
}

void TileMap::SetTile(TileTypes TileType, Vector2D<int> TileCoordinate) {
    if (TileCoordinate.x >= 0 && TileCoordinate.x < MapHeight && TileCoordinate.y >= 0 && TileCoordinate.y < MapWidth) {
        Tiles[TileCoordinate.y][TileCoordinate.x] = TileType;
    }
}

void TileMap::Draw() {
    for (int row = 0; row < MapHeight; row++) {
        for (int column = 0; column < MapWidth; column++) {
            SDL_Rect DestinationRectangle{column * TILE_HEIGHT, row * TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT};
            SDL_Rect SourceRectangle{0, 0, TILE_WIDTH, TILE_HEIGHT};
            switch (Tiles[row][column]) {
                case TileTypes::Water:
                    TextureManager::Draw(Renderer, Water, SourceRectangle, DestinationRectangle);
                    break;

                case TileTypes::Dirt:
                    TextureManager::Draw(Renderer, Dirt, SourceRectangle, DestinationRectangle);
                    break;

                case TileTypes::Grass:
                    TextureManager::Draw(Renderer, Grass, SourceRectangle, DestinationRectangle);
                    break;

                case TileTypes::TrackVertical:
                    TextureManager::Draw(Renderer, Track, SourceRectangle, DestinationRectangle, 90);
                    break;

                case TileTypes::TrackHorizontal:
                    TextureManager::Draw(Renderer, Track, SourceRectangle, DestinationRectangle);
                    break;

                default:
                    TextureManager::Draw(Renderer, Water, SourceRectangle, DestinationRectangle);
                    break;
            }
        }
    }
}
