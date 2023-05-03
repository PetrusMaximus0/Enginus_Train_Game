#pragma once
#include "RailwayPoint.h"
#include <SDL.h>
#include "TextureManager.h"

RailwayPoint::RailwayPoint(SDL_Renderer* InRenderer, const char* TextureSheet, Vector2D<int> InCoordinates) : 
	GameObject(InRenderer, TextureSheet, InCoordinates)
{


}

RailwayPoint::~RailwayPoint()
{
}

void RailwayPoint::InitializePoint()
{

}

void RailwayPoint::ConnectPoints()
{
}

void RailwayPoint::DisconnectPoints()
{
}

void RailwayPoint::Update()
{
	GameObject::Update();
}

void RailwayPoint::Render()
{
	GameObject::Render();
}
