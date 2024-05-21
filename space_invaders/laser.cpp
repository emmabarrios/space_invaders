#include "laser.h"

Laser::Laser(Vector2 position, int speed) {
	this->position = position;
	this->speed = speed;
	active = true;
}

void Laser::Update() {
	position.y += speed;
	if (active) {
		if (position.x > GetScreenHeight() || position.y < 0) {
			active = false;
		}
	}
}

void Laser::Draw() {
	if (active) {
		Color sand = { 243, 216, 63, 255 };
		DrawRectangle(position.x, position.y, 4, 15, sand);
	}
}
