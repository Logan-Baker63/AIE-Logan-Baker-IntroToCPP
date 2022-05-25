#include "Ball.h"
#include "Game.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>

using namespace std;



Ball::Ball(Texture2D texture, Vector2 position, Color colour, bool ballControl, bool ballControlLastPlayerOnly, bool invinceAbility, int xSpeed, int ySpeed, int speedLimit)
{
	Texture = texture;
	Position = position;
	Colour = colour;

	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	SpeedLimit = speedLimit;

	this->ballControl = ballControl;
	this->ballControlLastPlayerOnly = ballControlLastPlayerOnly;
	this->invinceAbility = invinceAbility;
}

float startTimer = 0;
Vector2 normalSpeed;

void Ball::Start() 
{
	isSlow = true;

	lastPlayer = 0;

	int temp = std::rand() % 3;

	if (temp == 0) {
		int temp1 = std::rand() % 2;
		if (temp1 == 0) {
			dir.y = 150;
		}
		else if (temp1 == 1) {
			dir.y = -150;
		}
		
		int temp2 = std::rand() % 2;
		if (temp2 == 0) {
			dir.x = 500;
		}
		else if (temp2 == 1) {
			dir.x = -500;
		}
	}
	else if (temp == 1) {
		int temp1 = std::rand() % 2;
		if (temp1 == 0) {
			dir.y = 190;
		}
		else if (temp1 == 1) {
			dir.y = -190;
		}

		int temp2 = std::rand() % 2;
		if (temp2 == 0) {
			dir.x = 460;
		}
		else if (temp2 == 1) {
			dir.x = -460;
		}
	}
	else if (temp == 2) {
		int temp1 = std::rand() % 2;
		if (temp1 == 0) {
			dir.y = 250;
		}
		else if (temp1 == 1) {
			dir.y = -250;
		}

		int temp2 = std::rand() % 2;
		if (temp2 == 0) {
			dir.x = 400;
		}
		else if (temp2 == 1) {
			dir.x = -400;
		}
	}

	normalSpeed = dir;
	dir.x /= 2.5f;
	dir.y /= 2.5f;
}

void Ball::Update() 
{
	
	if (IsKeyDown(KEY_P)) {
		int p = 0;
	}
	
	if (ballControl) 
	{
		if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && InvinceAbilityCheck() && LastPlayerTouchBall(1))
		{
			if (IsKeyDown(KEY_W)) {
				/*if (dir.x < 0) {
					dir.x += 2.5f;
				}
				else {
					dir.x += 2.5f;
				}*/

				if (dir.y < SpeedLimit) {
					dir.x -= xSpeed;
					dir.y += ySpeed;
				}

				
			}

			if (IsKeyDown(KEY_S)) {
				/*if (dir.x < 0) {
					dir.x += 2.5f;
				}
				else {
					dir.x += 2.5f;
				}*/

				if (dir.y > -SpeedLimit) {
					dir.x -= xSpeed;
					dir.y -= ySpeed;
				}
				
			}
		}

		if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && InvinceAbilityCheck() && LastPlayerTouchBall(2))
		{
			if (IsKeyDown(KEY_UP)) {
				/*if (dir.x < 0) {
					dir.x += 2.5f;
				}
				else {
					dir.x += 2.5f;
				}*/

				if (dir.y < SpeedLimit) {
					dir.x += xSpeed;
					dir.y += ySpeed;
				}
				
			}

			if (IsKeyDown(KEY_DOWN)) {
				/*if (dir.x < 0) {
					dir.x += 2.5f;
				}
				else {
					dir.x += 2.5f;
				}*/

				if (dir.y > -SpeedLimit) {
					dir.x += xSpeed;
					dir.y -= ySpeed;
				}
				
			}
		}
	}
	


	if (Position.x >= GetScreenWidth())
	{
		// Player 1 Point
		Start();
		Position = raylib::Vector2(290, 290);
		Player1Score++;
	}
	
	if (Position.x <= 0) 
	{
		// Player 2 Point
		Start();
		Position = raylib::Vector2(290, 290);
		Player2Score++;
	}

	if (Position.x > Player1Pos.x && Position.x < Player1Pos.x + 10) 
	{
		if (Position.y > Player1Pos.y - 15 && Position.y < Player1Pos.y + 65 + 5) 
		{
			// Collided with player 1

			lastPlayer = 1;

			if (isSlow) {
				dir.x = normalSpeed.x;
				dir.y = normalSpeed.y;
				isSlow = false;
			}

			if (hitInvert1) {
				dir = raylib::Vector2(-abs(dir.x * 1.0f), -dir.y * 1.0f);
			}
			else {
				dir = raylib::Vector2(-abs(dir.x), dir.y);
			}
			
		}
	}

	if (Position.x >= Player2Pos.x - 10 && Position.x < Player2Pos.x + 10)
	{
		if (Position.y > Player2Pos.y - 15 && Position.y < Player2Pos.y + 65 + 5)
		{
			// Collided with player 2

			lastPlayer = 2;

			if (isSlow) {
				dir.x = normalSpeed.x;
				dir.y = normalSpeed.y;
				isSlow = false;
			}

			if (hitInvert2) {
				dir = raylib::Vector2(abs(dir.x * 1.0f), -dir.y * 1.0f);
			}
			else {
				dir = raylib::Vector2(abs(dir.x), dir.y);
			}
			
		}
	}

	// Collided with the roof
	if (Position.y <= 0)
	{
		
		if ((IsKeyDown(KEY_D) && IsKeyDown(KEY_A)) || ((IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)))) {

		}

		dir = raylib::Vector2(dir.x, -abs(dir.y));
	}

	// Collided with the ground
	if (Position.y >= 600)
	{
		
		if ((IsKeyDown(KEY_D) && IsKeyDown(KEY_A)) || ((IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)))) {

		}
		dir = raylib::Vector2(dir.x, abs(dir.y));
	}

	Move(dir);

	
}

bool Ball::InvinceAbilityCheck() {
	if (invinceAbility) {
		if ((IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)) || (IsKeyDown(KEY_A) && IsKeyDown(KEY_D))) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}

bool Ball::LastPlayerTouchBall(int player) {
	if (ballControlLastPlayerOnly) {
		if (player == lastPlayer) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}


float timer = 0;
float timer2 = 0;

void Ball::Draw()
{
	if (!InvinceAbilityCheck()) {
		Colour = GOLD;
		timer += GetFrameTime();
		if (timer >= 0.3f) {
			Colour = GOLD;
			DrawTextureEx(Texture, Position, 0, 1, Colour);
			timer2 += GetFrameTime();
			if (timer2 >= 0.35f) {
				timer = 0;
				timer2 = 0;
			}
		}
	}
	else {
		Colour = WHITE;
		DrawTextureEx(Texture, Position, 0, 1, Colour);
	}
	

	

	char* score1;
	string str1 = to_string(Player1Score);
	score1 = &str1[0];

	char* score2;
	string str2 = to_string(Player2Score);
	score2 = &str2[0];

	DrawText(score1, 150 - MeasureText(score1, 40), 150, 40, RAYWHITE);
	DrawText(score2, GetScreenWidth() - 150 - MeasureText(score2, 40), 150, 40, RAYWHITE);

}

void Ball::Move(Vector2 dir) 
{
	Position.x -= dir.x * GetFrameTime();
	Position.y -= dir.y * GetFrameTime();
}