#pragma once
#include "raylib.h"

class Alien {
public:
	Alien(int type, Vector2 position);
	void Udate(int direction);
	void Draw();
	int GetType();
	static Texture2D alienImages[3];
	static void UnloadImages();
	int type;
	Vector2 position;
	Rectangle GetRect();
private:
};	