#pragma once
#include "Components.h"

class PositionComponent : public Component {

private:
	Vector2D<int> Position{ 0,0 };

public:
	PositionComponent() {
	}

	PositionComponent(int inX, int inY) {
		Position.x = inX;
		Position.y = inY;
	}
		
	
	Vector2D<int> GetPosition() {
		return Position;
	}

	void Init() override {
		Position.x = 0;
		Position.y = 0;
	}

	void Update() override {
		/*Temporary*/
		Position.x++;
		Position.y++;
	}
	void SetPos(int X, int Y) {
		Position.x = X;
		Position.y = Y;
	}


};