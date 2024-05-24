#pragma once
#include "raylib.h"
#include "laser.h"
#include <vector>

class Spaceship {
public:
	Spaceship();
	~Spaceship();
	void Draw();
	void MoveRight();
	void MoveLeft();
	void FireLaser();
	std::vector<Laser> lasers;
	Rectangle GetRect();
private:
	Texture2D image;
	Vector2 position;
	double lastFireTime;
};

