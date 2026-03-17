#include <raylib.h>
#include <iostream>
#include <vector>
//enemy
struct Enemy {
	float speed = 4;
	float enemyX = 600;
	float enemY = 0;
	int enemyH = 40;
	int enemyW = 20;
};
//player
struct Player
{
	float playerx = 100;
	float playery = 0;
	bool isonGround = true;
	int playerheight = 40;
	int playerwidth = 20;

	float jumpforce = 13;
	float velocity = 0;
	float gravity = 0.6;
};
//ground
struct Ground
{
	int groundX = 0;
	int groundY = 0;
	int groundW = 0;
	int groundH = 0;
};
//game state 
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
	Ground ground1;
	ground1.groundX = 0;
	ground1.groundY = WindowHeight-30;
	ground1.groundH = 30;
	ground1.groundW = WindowWidth;
	Player dinosaurus;
	dinosaurus.playery = WindowHeight - 70;
	Enemy enemy;
	enemy.enemY = ground1.groundY - 40;
	Rectangle playerRect;
	Rectangle enemyRect;
	float score = 0;
	float scoreSpeed = 5;
	float delta;


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
			delta = GetFrameTime();

			if (IsKeyPressed(KEY_SPACE) && dinosaurus.isonGround) {
				dinosaurus.velocity = -dinosaurus.jumpforce;
				dinosaurus.isonGround = false;
			}
			if (!dinosaurus.isonGround) {
				dinosaurus.velocity += dinosaurus.gravity;
				dinosaurus.playery += dinosaurus.velocity;
			}
			if (dinosaurus.playery + dinosaurus.playerheight >= ground1.groundY) {
				dinosaurus.velocity = 0;
				dinosaurus.isonGround = true;
				dinosaurus.playery = ground1.groundY - dinosaurus.playerheight;
			}
			enemy.enemyX -= enemy.speed;
			if (enemy.enemyX + enemy.enemyW < 0) {
				enemy.enemyX = WindowWidth;
			}

			playerRect.x = dinosaurus.playerx;
			playerRect.y = dinosaurus.playery;
			playerRect.width = dinosaurus.playerwidth;
			playerRect.height = dinosaurus.playerheight;

			enemyRect.x = enemy.enemyX;
			enemyRect.y = enemy.enemY;
			enemyRect.width = enemy.enemyW;
			enemyRect.height = enemy.enemyH;

			if (CheckCollisionRecs(playerRect, enemyRect)) {
				currentState = GameOver;
			}
			score += scoreSpeed * delta;
			break;
		case Pause:
			if (IsKeyPressed(KEY_P)) {
				currentState = PlayGame;
			}
			break;
		case GameOver:
			if (IsKeyPressed(KEY_SPACE)) {
				dinosaurus.playery = ground1.groundY - dinosaurus.playerheight;
				dinosaurus.velocity = 0;
				dinosaurus.isonGround = true;
				score = 0;

				// Reset Enemy
				enemy.enemyX = WindowWidth; // vraćamo neprijatelja sa desne strane
				enemy.enemY = ground1.groundY - enemy.enemyH;

				// Promeni stanje igre na PlayGame
				currentState = PlayGame;
			}
			break;
		default:
			break;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		switch (currentState)
		{
		case Menu:
			DrawText("Press Enter to start game!", WindowWidth / 2-200, WindowHeight / 2, 30, YELLOW);
			DrawText("Press Escape to exit!", WindowWidth / 2-200, WindowHeight / 2 + 100, 30, YELLOW);
			break;
		case PlayGame:
			DrawRectangle(ground1.groundX, ground1.groundY, ground1.groundW, ground1.groundH, WHITE);
			DrawRectangle(dinosaurus.playerx, dinosaurus.playery, dinosaurus.playerwidth, dinosaurus.playerheight, GREEN);
			DrawRectangle(enemy.enemyX, enemy.enemY, enemy.enemyW, enemy.enemyH, RED);
			DrawText(TextFormat("Score: %d", (int)score), 350, 200, 30, YELLOW);


			break;
		case Pause:
			DrawText("Game is paused", WindowWidth / 2-150, WindowHeight / 2, 40, BLUE);
			break;
		case GameOver:
			DrawText("You lost, press space to restart!", WindowWidth / 2 - 200, WindowHeight / 2, 30, RED);
			break;
		default:
			break;
		}
		EndDrawing();
	}
	CloseWindow();
}