#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FileName)
{
    SDL_Texture* TempTexture = IMG_LoadTexture(Game::Renderer, FileName);
    if (TempTexture == NULL)
        std::cout << "ERROR - Failed to Load Texture in " << FileName << std::endl;

    return TempTexture;
}
