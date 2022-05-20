#include "Ball.h"
#include "Game.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>


using namespace std;

Vector2 dir = raylib::Vector2(0, 0);

Ball::Ball(Texture2D texture, Vector2 position)
{
	Texture = texture;
	Position = position;
	
}

void Ball::Start() 
{
	isSlow = true;

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

	dir.x /= 2.5f;
	dir.y /= 2.5f;
}

void Ball::Update() 
{
	
	if (IsKeyDown(KEY_A)) 
	{
		if (IsKeyDown(KEY_W)) {
			/*if (dir.x < 0) {
				dir.x += 2.5f;
			}
			else {
				dir.x += 2.5f;
			}*/
			dir.x -= 2.5f;
			dir.y += 2.5f;
		}

		if (IsKeyDown(KEY_S)) {
			/*if (dir.x < 0) {
				dir.x += 2.5f;
			}
			else {
				dir.x += 2.5f;
			}*/
			dir.x += 2.5f;
			dir.y -= 2.5f;
		}
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		if (IsKeyDown(KEY_UP)) {
			/*if (dir.x < 0) {
				dir.x += 2.5f;
			}
			else {
				dir.x += 2.5f;
			}*/
			dir.x -= 2.5f;
			dir.y += 2.5f;
		}

		if (IsKeyDown(KEY_DOWN)) {
			/*if (dir.x < 0) {
				dir.x += 2.5f;
			}
			else {
				dir.x += 2.5f;
			}*/
			dir.x += 2.5f;
			dir.y -= 2.5f;
		}
	}


	if (Position.x >= 600 + 600)
	{
		// Player 1 Point
		Start();
		Position = raylib::Vector2(290, 290);
		Player1Score++;
	}
	
	if (Position.x <= 0 - 600) 
	{
		// Player 2 Point
		Start();
		Position = raylib::Vector2(290, 290);
		Player2Score++;
	}

	if (Position.x > Player1Pos.x && Position.x < Player1Pos.x + 10) 
	{
		if (Position.y > Player1Pos.y - 15 && Position.y < Player1Pos.y + 65 + 15) 
		{
			// Collided with player 1

			if (isSlow) {
				dir.x *= 2.5f;
				dir.y *= 2.5f;
				isSlow = false;
			}

			if (hitInvert1) {
				dir = raylib::Vector2(-abs(dir.x), -dir.y);
			}
			else {
				dir = raylib::Vector2(-abs(dir.x), dir.y);
			}
			
		}
	}

	if (Position.x >= Player2Pos.x - 3 && Position.x < Player2Pos.x + 10)
	{
		if (Position.y > Player2Pos.y - 15 && Position.y < Player2Pos.y + 65 + 15)
		{
			// Collided with player 2

			if (isSlow) {
				dir.x *= 2.5f;
				dir.y *= 2.5f;
				isSlow = false;
			}

			if (hitInvert2) {
				dir = raylib::Vector2(abs(dir.x), -dir.y);
			}
			else {
				dir = raylib::Vector2(abs(dir.x), dir.y);
			}
			
		}
	}

	if (Position.y <= 0)
	{
		// Collided with the roof
		dir = raylib::Vector2(dir.x, -abs(dir.y));
	}

	if (Position.y >= 600)
	{
		// Collided with the ground
		dir = raylib::Vector2(dir.x, abs(dir.y));
	}

	Move(dir);
}

void Ball::Draw()
{
	DrawTextureEx(Texture, Position, 0, 1, WHITE);

	

	char* score1;
	string str1 = to_string(Player1Score);
	score1 = &str1[0];

	char* score2;
	string str2 = to_string(Player2Score);
	score2 = &str2[0];

	DrawText(score1, 150 - MeasureText(score1, 40), 150, 40, RAYWHITE);
	DrawText(score2, 450 - MeasureText(score2, 40), 150, 40, RAYWHITE);

}

void Ball::Move(Vector2 dir) 
{
	Position.x -= dir.x * GetFrameTime();
	Position.y -= dir.y * GetFrameTime();
}