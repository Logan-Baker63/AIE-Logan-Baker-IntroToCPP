#include "Game.h"
#include "Player.h"
#include "Ball.h"
//#include <cstring>

using namespace std;

Player* Player1;
Player* Player2;
Ball* ball;
/*Ball* ball2;

float timer = 0;
bool timerFinished = false;*/

Game::Game() 
{
	defaultBatTex = LoadTextureFromImage(LoadImage("Textures/PongExtraSmall.png"));
	defaultBallTex = LoadTextureFromImage(LoadImage("Textures/PongBall.png"));
}

void Game::Start() 
{
	Player1 = new Player(defaultBatTex, raylib::Vector2(40, 225));
	Player2 = new Player(defaultBatTex, raylib::Vector2(550, 225));

	ball = new Ball(defaultBallTex, raylib::Vector2(290, 290));
	ball->Start();

	
}

void Game::Update() 
{
	/*timer += GetFrameTime();

	if (timer >= 20 && !timerFinished) {
		ball2 = new Ball(defaultBallTex, raylib::Vector2(290, 290));
		ball2->Start();
		timerFinished = true;
	}*/
	
	
	

	

	/*if (timerFinished)
	{
		ball2->Player1Pos = Player1->Position;
		ball2->Player2Pos = Player2->Position;

		ball2->Update();
	}*/

	// Handles Movement

	//Player 1
	if (IsKeyDown(KEY_W)) 
	{
		Player1->Position.y -= PlayerSpeed * GetFrameTime();
		ball->Player1Pos = Player1->Position;
		if (Player1->Position.y < 0) {
			Player1->Position.y = 0;
		}
	}
	else if (IsKeyDown(KEY_S)) 
	{
		Player1->Position.y += PlayerSpeed * GetFrameTime();
		ball->Player1Pos = Player1->Position;
		if (Player1->Position.y > 600 - 65) {
			Player1->Position.y = 600 - 65;
		}
	}

	// Player 2
	if (IsKeyDown(KEY_DOWN)) 
	{
		Player2->Position.y += PlayerSpeed * GetFrameTime();
		ball->Player2Pos = Player2->Position;
		if (Player2->Position.y > 600 - 65) {
			Player2->Position.y = 600 - 65;
		}
	}
	else if (IsKeyDown(KEY_UP)) 
	{
		Player2->Position.y -= PlayerSpeed * GetFrameTime();
		ball->Player2Pos = Player2->Position;
		if (Player2->Position.y < 0) {
			Player2->Position.y = 0;
		}
	}

	ball->Update();

}

void Game::Draw() 
{
	Player1->Draw();
	Player2->Draw();
	ball->Draw();

	/*if (timer >= 20) {
		ball2->Draw();
	}*/
	
}