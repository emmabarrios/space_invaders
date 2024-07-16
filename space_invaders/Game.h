#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mystery_ship.h"
#include <iostream>

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
	bool run;
	int lives;

private:
	Spaceship spaceship;
	MysteryShip mysteryShip;
	void DeleteInactiveLasers();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShootLaser();
	void CheckForCollisions();
	void GameOver();
	void Reset();
	void InitGame();
	std::vector<Obstacle> obstacles;
	std::vector<Obstacle> CreateObstacle();
	std::vector<Alien> CreateAliens();
	std::vector<Alien> aliens;
	std::vector<Laser> alienLasers;
	int alienDirection;
	constexpr static float alienLaserShootInterval = 0.36;
	float timeLastAlienFired;
	float mysterShipSpawnInterval;
	float timeLastSpawn;
};

