#include <raylib.h>
#include <iostream>

int main() {
	int WindowHeight = 600;
	int WindowWidth = 800;
	InitWindow(WindowWidth, WindowHeight, "Dinosaurus game!");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		//Update logic
		BeginDrawing();
		ClearBackground(RED);
		EndDrawing();
	}
	CloseWindow();
}