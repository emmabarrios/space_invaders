#include "Game.h"
#include <fstream>

Game::Game() {
	music = LoadMusicStream("assets/sounds/music.ogg");
	explosionSound = LoadSound("assets/sounds/explosion.ogg");
	PlayMusicStream(music);
	InitGame();
}

Game::~Game() {
	Alien::UnloadImages();
	UnloadMusicStream(music);
	UnloadSound(explosionSound);
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

	if (run) {
		double currentTime = GetTime();

		if (currentTime - timeLastSpawn > mysterShipSpawnInterval) {
			mysteryShip.Spawn();
			timeLastSpawn = GetTime();
			mysterShipSpawnInterval = GetRandomValue(10, 20);
		}

		for (auto& laser : spaceship.lasers) {
			laser.Update();
		}

		MoveAliens();

		AlienShootLaser();

		for (auto& laser : alienLasers) {
			laser.Update();
		}

		DeleteInactiveLasers();
		mysteryShip.Update();

		CheckForCollisions();
	}
	else {
		if (IsKeyDown(KEY_ENTER)) {
			Reset();
			InitGame();
		}
	}
}

void Game::HandleInput() {

	if (run) {
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
		alien.Update(alienDirection);

		int position = alien.position.x;
		int imageWidth = alien.alienImages[alien.type - 1].width;
		int location = position + imageWidth;

		if (position + imageWidth > GetScreenWidth() -25 || position <= 25)
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

void Game::CheckForCollisions()
{
	// Spaceship lasers
	for (auto& laser : spaceship.lasers)
	{
		// we made an iterator and made it to point to the beginning of the aliens vector
		auto iterator = aliens.begin();

		while (iterator != aliens.end())
		{
			if (CheckCollisionRecs(iterator->GetRect(), laser.GetRect()))
			{
				PlaySound(explosionSound);

				if (iterator->type == 1) {
					score += 100;
				}
				else if (iterator->type == 2) {
					score += 200;
				}
				else if (iterator->type == 3) {
					score += 300;
				}

				CheckForHighscore();

				iterator = aliens.erase(iterator);
				laser.active = false;
			}
			else {
				++iterator;
			}
		}

		for (auto& obstacle : obstacles) {
			auto iterator = obstacle.blocks.begin();
			
			while (iterator!= obstacle.blocks.end())
			{
				if (CheckCollisionRecs(iterator->GetRect(),laser.GetRect()))
				{
					iterator = obstacle.blocks.erase(iterator);
					laser.active = false;
				}
				else {
					++iterator;
				}
			}
		}

		if (CheckCollisionRecs(mysteryShip.GetRect(), laser.GetRect()))
		{
			PlaySound(explosionSound);
			mysteryShip.alive = false;
			laser.active = false;
			score += 500;
			CheckForHighscore();
		}
	}
	
	// Alien lasers
	for (auto& laser : alienLasers) {
		if (CheckCollisionRecs(laser.GetRect(), spaceship.GetRect()))
		{
			laser.active = false;
			lives --;
			if (lives == 0) {
				GameOver();
			}
		}

		for (auto& obstacle : obstacles) {
			auto iterator = obstacle.blocks.begin();

			while (iterator != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(iterator->GetRect(), laser.GetRect()))
				{
					iterator = obstacle.blocks.erase(iterator);
					laser.active = false;
				}
				else {
					++iterator;
				}
			}
		}
	}

	// Alien collision with obstacle
	for (auto& alien : aliens) {
		for (auto& obstacle : obstacles) {
			auto iterator = obstacle.blocks.begin();
			while (iterator != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(iterator->GetRect(), alien.GetRect()))
				{
					iterator = obstacle.blocks.erase(iterator); 
				}
				else {
					iterator++;

				}
			}
		}

		if (CheckCollisionRecs(alien.GetRect(), spaceship.GetRect()))
		{
			GameOver();
		}
	}
}

void Game::GameOver() {
	run = false;
}

void Game::Reset() {
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
}

void Game::InitGame() {
	obstacles = CreateObstacle();
	aliens = CreateAliens();
	alienDirection = 1;
	timeLastAlienFired = 0;
	timeLastSpawn = 0.0;
	mysterShipSpawnInterval = GetRandomValue(10, 20);
	lives = 3;
	run = true;
	score = 0;
	//highscore = 0;
	LoadGame(this);
}

void Game::CheckForHighscore() {
	if (score > highscore) {
		highscore = score;
		SaveGame(highscore);
	}
}

void Game::SaveGame(int highscore) {
	std::ofstream gameSaveFile("gameSave.txt");
	if (gameSaveFile.is_open()) {
		gameSaveFile << highscore;
		gameSaveFile.close();
	}
	else {
		std::cerr << "Failed to save highscore to file" << std::endl;
	}
}

void Game::LoadGame(Game* game) {
	int loadedHighscore = 0;
	std::ifstream gameSaveFile("gameSave.txt");
	if (gameSaveFile.is_open()) {
		gameSaveFile >> loadedHighscore;
		gameSaveFile.close();
	}
	else {
		std::cerr << "Failed to load highscore to file" << std::endl;
	}
	game->highscore = loadedHighscore;
}

std::vector<Obstacle> Game::CreateObstacle()
{
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
	for (int i = 0; i < 4; i++)
	{
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
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
