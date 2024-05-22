#include "raylib.h"
#include "Game.h"


int main() {
	Color grey = {29,29,27,255};

	int w = 750;
	int h = 700;

	InitWindow(w,h,"Space Invaders");
	SetTargetFPS(60);

	Game game;


	while (WindowShouldClose() == false) {
		game.HandleInput();
		game.Update();

		BeginDrawing();
		ClearBackground(grey);
		
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}