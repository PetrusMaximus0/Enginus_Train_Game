#pragma once
#include "GameObject.h"

class Train : public GameObject
{

private:
	bool IsMoving{};
	char Identifier[2]{};
	int CarSize{};
	SDL_Texture* CarTextures[4]{};
	Vector2D<int> CarCoordinates[4]{};

public:
	Train(SDL_Renderer* InRenderer, Vector2D<int> InCoordinate, bool InIsMoving, int InCarSize, const char* InIdentifier);

	void Update() override;

	void Render() override;
	
	void InitializeTrainCoordinates(Vector2D<int> InCoordinate);

	void SetWagonTexture(GACarColor NewColor, int WagonID);

	void MoveTrain(Vector2D<int> NewCoordinates);

	void SetIsMoving(bool Moving);

	bool GetIsMoving();

	Vector2D<int> GetCoordinates();

	void PrintTrainDetails(bool OnlyCoordinates);

};

