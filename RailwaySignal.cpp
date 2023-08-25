#pragma once
#include "RailwaySignal.h"
#include "TextureManager.h"

RailwaySignal::RailwaySignal(SDL_Renderer* InRenderer, Vector2D<int> InCoordinates, Vector2D<int> InTargetPosition, bool InGreenLight = true): 
	GameObject(InRenderer, InCoordinates),
	GreenLight(InGreenLight),
	TargetPosition(InTargetPosition)
{
	SetGreenLight(InGreenLight);
}

RailwaySignal::~RailwaySignal()
{

}

void RailwaySignal::Update() {
	GameObject::Update();
}

void RailwaySignal::Render() {
	GameObject::Render();

}

void RailwaySignal::SetGreenLight(bool Value = true) {
	GreenLight = Value;
	if (Value) {
		SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/railway_light_green.png"));
	}
	else {
		SetTexture(TextureManager::LoadTexture(Renderer, "assets/art/railway_light_red.png"));
	}
}

bool RailwaySignal::GetGreenLight() {return GreenLight;}

Vector2D<int> RailwaySignal::GetTargetPosition() { return TargetPosition; }