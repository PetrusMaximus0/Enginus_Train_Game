#pragma once
#include "EntityComponentSystem.h"
#include "Library.h"
class PositionComponent : public Component {

private:
	Vector2D<int> Position{0,0};

public:
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