#pragma once
#include "RailwaySignal.h"
#include "TextureManager.h"

RailwaySignal::RailwaySignal(SDL_Renderer* InRenderer, TransformComponent InTransform, Vector2D<float> InTargetPosition, bool InGreenLight = true):
	GameObject(InRenderer, InTransform),
	GreenLight(InGreenLight),
	TargetPosition(InTargetPosition)
{
	SetGreenLight(InGreenLight);
}

RailwaySignal::~RailwaySignal()
{

}

void RailwaySignal::Update(float DeltaTime) {
	GameObject::Update(DeltaTime);
}

void RailwaySignal::Render() {
	GameObject::Render();

}

void RailwaySignal::SetGreenLight(bool Value = true) {
	GreenLight = Value;
	if (Value) {
		SpriteComp->SetTexture("assets/art/railway_light_green.png");
	}
	else {
		SpriteComp->SetTexture("assets/art/railway_light_red.png");
	}
}

bool RailwaySignal::GetGreenLight() {return GreenLight;}

Vector2D<float> RailwaySignal::GetTargetPosition() { return TargetPosition; }