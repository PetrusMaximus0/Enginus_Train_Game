#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* Renderer, const char* FileName)
{
    SDL_Texture* TempTexture = IMG_LoadTexture(Renderer, FileName);
    if (Renderer == nullptr)
        std::cout << "ERROR - Renderer pointer is null when attemping to load a texture" << std::endl;

    if (TempTexture == NULL)
        std::cout << "ERROR - Failed to Load Texture in " << FileName << std::endl;

    return TempTexture;
}

void TextureManager::Draw(SDL_Renderer* Renderer, SDL_Texture* Texture, SDL_Rect Source, SDL_Rect Destination, double Heading)
{
    SDL_RenderCopyEx(Renderer, Texture, &Source, &Destination, Heading, NULL, SDL_FLIP_NONE);
}
