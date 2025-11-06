#pragma once
#include "GameObject.h"
#include "Library.h"

class RailwaySignal : public GameObject {
    Vector2D<float> TargetPosition;
    bool GreenLight = false;

public:
    RailwaySignal(SDL_Renderer *InRenderer, TransformComponent InTransform, Vector2D<float> InTargetPosition,
                  bool InGreenLight);

    ~RailwaySignal();

    void Update(float DeltaTime);

    void Render();

    void SetGreenLight(bool Value);

    bool GetGreenLight();

    Vector2D<float> GetTargetPosition();
};
