#include "Ball.h"
#include "Game.h"

using namespace std;

Vector2 dir = raylib::Vector2(400, 250);

Ball::Ball(Texture2D texture, Vector2 position)
{
	Texture = texture;
	Position = position;
	
}

void Ball::Start() 
{
	
}

void Ball::Update() 
{
	

	if (Position.x >= 600)
	{
		// Player 1 Point
		Position = raylib::Vector2(290, 290);
		Player1Score++;
	}
	
	if (Position.x <= 0) 
	{
		// Player 2 Point
		Position = raylib::Vector2(290, 290);
		Player2Score++;
	}

	if (Position.x > Player1Pos.x && Position.x < Player1Pos.x + 10) 
	{
		if (Position.y > Player1Pos.y - 15 && Position.y < Player1Pos.y + 65 + 15) 
		{
			// Collided with player 1
			dir = raylib::Vector2(-abs(dir.x), dir.y);
		}
	}

	if (Position.x >= Player2Pos.x - 3 && Position.x < Player2Pos.x + 10)
	{
		if (Position.y > Player2Pos.y - 15 && Position.y < Player2Pos.y + 65 + 15)
		{
			// Collided with player 2
			dir = raylib::Vector2(abs(dir.x), dir.y);
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

	if (IsKeyDown(KEY_P)) {
		int i = 0;
	}
}

void Ball::Move(Vector2 dir) 
{
	Position.x -= dir.x * GetFrameTime();
	Position.y -= dir.y * GetFrameTime();
}