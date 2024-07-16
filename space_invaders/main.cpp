#include "raylib.h"
#include "Game.h"


int main() {
	Color grey = {29,29,27,255};
	Color yellow = {243,216,63, 255};

	int offset = 50;
	int w = 750;
	int h = 700;

	InitWindow(w + offset,h + 2 * offset,"Space Invaders");

	Font font = LoadFontEx("Font/monogram.ttf", 64,0 ,0);
	Texture2D spaceshipImage = LoadTexture("assets/images/spaceship.png");

	SetTargetFPS(60);

	Game game;


	while (WindowShouldClose() == false) {
		game.HandleInput();
		game.Update();

		BeginDrawing();
		ClearBackground(grey);
		
		DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
		DrawLineEx({25,730}, {775, 730}, 3, yellow);

		if (game.run) {
			DrawTextEx(font, "LEVEL 01", { 560, 740 }, 34, 3, yellow);
		}
		else {
			DrawTextEx(font, "GAME OVER", { 560, 740 }, 34, 3, yellow);
		}

		float x = 50.0;

		for (int i = 0; i < game.lives; i++) {
			DrawTextureV(spaceshipImage, {x, 745}, WHITE);
			x += 50;
		}

		game.Draw();
		EndDrawing();
	}

	CloseWindow();
}