#include "Game.h"

Game::Game() {
	obstacles = CreateObstacle();
}

Game::~Game() {
	
}

void Game::Draw() {
	spaceship.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
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

std::vector<Obstacle> Game::CreateObstacle()
{
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
	for (int i = 0; i < 4; i++)
	{
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 100) }));
	}

	return obstacles;
}
