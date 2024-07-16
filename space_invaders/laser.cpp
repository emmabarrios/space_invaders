#include "laser.h"

Laser::Laser(Vector2 position, int speed) {
	this->position = position;
	this->speed = speed;
	active = true;
}

void Laser::Update() {
	position.y += speed;
	if (active) {
		// creo que esta linea es la que causa el bug de que al final a la derecha no se pueda disparar
		//if (position.x > GetScreenHeight() || position.y < 0) {
		if (position.y > GetScreenHeight() || position.y < 0) {
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

Rectangle Laser::GetRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 4;
	rect.height = 15;

	return rect;
}
