#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
private:
	Spaceship spaceship;
	void DeleteInactiveLasers();
	void MoveAliens();
	void MoveDownAliens(int distance);
	void AlienShootLaser();
	std::vector<Obstacle> obstacles;
	std::vector<Obstacle> CreateObstacle();
	std::vector<Alien> CreateAliens();
	std::vector<Alien> aliens;
	std::vector<Laser> alienLasers;
	int alienDirection;
	constexpr static float alienLaserShootInterval = 0.36;
	float timeLastAlienFired;
};

