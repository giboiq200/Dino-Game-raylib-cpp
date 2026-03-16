#include <raylib.h>
#include <iostream>

enum GameState
{
	Menu,
	PlayGame,
	Pause,
	GameOver
};

int main() {
	int WindowHeight = 600;
	int WindowWidth = 800;
	InitWindow(WindowWidth, WindowHeight, "Dinosaurus game!");
	SetTargetFPS(60);
	GameState currentState = Menu;

	while (!WindowShouldClose()) {
		//Update logic
		switch (currentState)
		{
		case Menu:
			if (IsKeyPressed(KEY_ENTER)) {
				currentState = PlayGame;
			}
			break;
		case PlayGame:
			if (IsKeyPressed(KEY_P)) {
				currentState = Pause;
			}
			break;
		case Pause:
			if (IsKeyPressed(KEY_P)) {
				currentState = PlayGame;
			}
			break;
		case GameOver:
			break;
		default:
			break;
		}
		BeginDrawing();
		ClearBackground(RED);
		switch (currentState)
		{
		case Menu:
			DrawText("Press Enter to start game!", WindowWidth / 2-200, WindowHeight / 2, 30, YELLOW);
			DrawText("Press Escape to exit!", WindowWidth / 2-200, WindowHeight / 2 + 100, 30, YELLOW);
			break;
		case PlayGame:
			DrawText("Game is playing", WindowWidth / 2-200, WindowHeight / 2, 40, GREEN);
			break;
		case Pause:
			DrawText("Game is paused", WindowWidth / 2-200, WindowHeight / 2, 40, BLUE);
			break;
		case GameOver:
			break;
		default:
			break;
		}
		EndDrawing();
	}
	CloseWindow();
}