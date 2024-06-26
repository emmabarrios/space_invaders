#include "spaceship.h"

Spaceship::Spaceship() {
	image = LoadTexture("assets/images/spaceship.png");
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = (GetScreenHeight() - image.height);
	lastFireTime = 0;
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
}

void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveRight() {
	position.x += 7;
	if (position.x > GetScreenWidth() - image.width) {
		position.x = GetScreenWidth() - image.width;
	}
}

void Spaceship::MoveLeft() {
	position.x -= 7;
	if (position.x < 0) {
		position.x = 0;
	}
}

void Spaceship::FireLaser() {
	if (GetTime() - lastFireTime >= 0.1) {
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));
		lastFireTime = GetTime();
	}
}

Rectangle Spaceship::GetRect()
{
	// We have to cast the values because Rectangle expects floats
	return {position.x, position.y, float(image.width), float(image.height)};
}
