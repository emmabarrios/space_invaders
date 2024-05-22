#include "Game.h"

Game::Game() {
	obstacles = CreateObstacle();
	aliens = CreateAliens();
	alienDirection = 1;
	timeLastAlienFired = 0;
	timeLastSpawn = 0.0;
	mysterShipSpawnInterval = GetRandomValue(10, 20);
}

Game::~Game() {
	Alien::UnloadImages();
}

void Game::Draw() {
	spaceship.Draw();
	mysteryShip.Draw();

	for (auto& laser : spaceship.lasers) {
		laser.Draw();
	}

	for (auto& laser : alienLasers) {
		laser.Draw();
	}

	for (auto& obstacle : obstacles) {
		obstacle.Draw();
	}

	for (auto& alien : aliens)
	{
		alien.Draw();
	}
}

void Game::Update() {

	double currentTime = GetTime();

	if (currentTime - timeLastSpawn > mysterShipSpawnInterval)
	{
		mysteryShip.Spawn();
		timeLastSpawn = GetTime();
		mysterShipSpawnInterval = GetRandomValue(10, 20);
	}

	for (auto& laser: spaceship.lasers) {
		laser.Update();
	}

	MoveAliens();

	AlienShootLaser();

	for (auto& laser : alienLasers) {
		laser.Update();
	}

	DeleteInactiveLasers();
	mysteryShip.Update();
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

	for (auto iterator = alienLasers.begin(); iterator != alienLasers.end();) {
		if (!iterator->active) {
			iterator = alienLasers.erase(iterator);
		}
		else {
			++iterator;
		}
	}
}

void Game::MoveAliens()
{
	for (auto& alien : aliens) {
		alien.Udate(alienDirection);

		int position = alien.position.x;
		int imageWidth = alien.alienImages[alien.type - 1].width;
		int location = position + imageWidth;

		if (position + imageWidth > GetScreenWidth() || position <= 0)
		{
			alienDirection *= -1;
			MoveDownAliens(4);
		}

	}
}

void Game::MoveDownAliens(int distance)
{
	for (auto& alien : aliens) {
		alien.position.y += distance;
	}
}

void Game::AlienShootLaser()
{
	double currentTime = GetTime();

	if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
	{
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		float laserPosition_x = alien.position.x + alien.alienImages[alien.type - 1].width / 2;
		float laserPosition_y = alien.position.y + alien.alienImages[alien.type - 1].height / 2;
		alienLasers.push_back(Laser({ laserPosition_x, laserPosition_y }, 6));
	
		timeLastAlienFired = GetTime();
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

std::vector<Alien> Game::CreateAliens()
{
	std::vector<Alien> aliens;

	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			int alienType;
			if (row == 0)
			{
				alienType = 3;
			}
			else if (row == 1 || row == 2)
			{
				alienType = 2;
			}
			else { alienType = 1; }

			float x = 75 + column * 55;
			float y = 110 + row * 55;
			aliens.push_back(Alien(alienType, {x, y}));
		}
	}

	return aliens;
}
