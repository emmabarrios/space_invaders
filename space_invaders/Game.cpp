#include "Game.h"

Game::Game() {

}

Game::~Game() {
	
}

void Game::Draw() {
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	DeleteInactiveLasers();
}

void Game::Update() {
	for (auto& laser: spaceship.lasers) {
		laser.Update();
	}
}

void Game::HandleInput() {
	if (IsKeyDown(KEY_LEFT)) {
		spaceship.MoveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		spaceship.MoveRight();
	}
	
	if (IsKeyDown(KEY_SPACE)) {
		spaceship.FireLaser();
	}
}

void Game::DeleteInactiveLasers() {
	for (auto iterator = spaceship.lasers.begin(); iterator != spaceship.lasers.end();) {
		if (!iterator -> active) {
			iterator = spaceship.lasers.erase(iterator);
		}
		else {
			++ iterator;
		}
	}
}
