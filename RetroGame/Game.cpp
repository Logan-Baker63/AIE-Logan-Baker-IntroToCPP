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
	Player1 = new Player(defaultBatTex, raylib::Vector2(40, 225), WHITE);
	Player2 = new Player(defaultBatTex, raylib::Vector2(GetScreenWidth() - 50, 225), WHITE);

	ball = new Ball(defaultBallTex, raylib::Vector2(GetScreenWidth() / 2 - 10, 290), WHITE, ballControl, ballControlLastPlayerOnly, invinceAbility, xSpeed, ySpeed, angleLimit);
	ball->Start();

	
}

int Game::charArrayToInt(char* arr) {
	int i, value, r, flag;

	flag = 1;
	i = value = 0;

	for (i = 0; i < strlen(arr); ++i) {

		// if arr contain negative number
		if (i == 0 && arr[i] == '-') {
			flag = -1;
			continue;
		}

		r = arr[i] - '0';
		value = value * 10 + r;
	}

	value = value * flag;

	return value;

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
	if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_A))
	{
		Player1->Position.y -= PlayerSpeed * GetFrameTime();
		ball->Player1Pos = Player1->Position;
		if (Player1->Position.y < 0) {
			Player1->Position.y = 0;
		}
	}
	else if (IsKeyDown(KEY_S) && !IsKeyDown(KEY_A))
	{
		Player1->Position.y += PlayerSpeed * GetFrameTime();
		ball->Player1Pos = Player1->Position;
		if (Player1->Position.y > 600 - 65) {
			Player1->Position.y = 600 - 65;
		}
	}

	// Player 2
	if (IsKeyDown(KEY_DOWN) && ! IsKeyDown(KEY_RIGHT)) 
	{
		Player2->Position.y += PlayerSpeed * GetFrameTime();
		ball->Player2Pos = Player2->Position;
		if (Player2->Position.y > 600 - 65) {
			Player2->Position.y = 600 - 65;
		}
	}
	else if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_RIGHT))
	{
		Player2->Position.y -= PlayerSpeed * GetFrameTime();
		ball->Player2Pos = Player2->Position;
		if (Player2->Position.y < 0) {
			Player2->Position.y = 0;
		}
	}

	if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && deflectAbility) {
		ball->hitInvert2 = true;
		Player2->Colour = DARKGRAY;
	}
	else {
		ball->hitInvert2 = false;
		Player2->Colour = WHITE;
	}

	if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && deflectAbility) {
		ball->hitInvert1 = true;
		Player1->Colour = DARKGRAY;
	}
	else {
		ball->hitInvert1 = false;
		Player1->Colour = WHITE;
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