#include "Ball.h"
#include "Game.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
//#include "CursedPong.h"

using namespace std;

//CursedPong cursedPong;
//Game game;


// constructor for ball provides it with information
Ball::Ball(Texture2D texture, Vector2 position, Color colour, bool ballControl, bool ballControlLastPlayerOnly, bool invinceAbility, int xSpeed, int ySpeed, int speedLimit, int winReq)
{
	//cursedPong = CursedPong();
	//game = Game();

	// sets the ball's local values to the respective ones from the game script

	Texture = texture;
	Position = position;
	Colour = colour;

	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	SpeedLimit = speedLimit;
	WinReq = winReq;

	this->ballControl = ballControl;
	this->ballControlLastPlayerOnly = ballControlLastPlayerOnly;
	this->invinceAbility = invinceAbility;
}

float startTimer = 0;
Vector2 normalSpeed;

void Ball::Start() 
{
	isSlow = true; // starts the ball slow

	lastPlayer = 0; // last player is set to no one so no one can ball control if the setting is on when it spawns

	// randomizes the ball spawn location 

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

	normalSpeed = dir; // sets the normal ball speed to change back to once someone hits ball for first time
	dir.x /= 2.5f;
	dir.y /= 2.5f;
}

void Ball::Update() 
{
	
	if (IsKeyPressed(KEY_P)) { // place breakpoint in here for easy pause debug
		int p = 0;
	}

	if (ballControl) // if ball control is on in settings menu
	{
		// checks if player 1 is allowed to use ball control
		if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && InvinceAbilityCheck() && LastPlayerTouchBall(1))
		{
			// handles using ball control for player 1
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

		// checks if player 2 is allowed to use ball control
		if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && InvinceAbilityCheck() && LastPlayerTouchBall(2))
		{
			// handles using ball control for player 2
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
	

	// scores for player 1 if ball goes off right side of screen
	if (Position.x >= GetScreenWidth())
	{
		// Player 1 Point
		Start();
		Position = raylib::Vector2(GetScreenWidth() / 2, GetScreenHeight() / 2);
		Player1Score++;
	}
	
	// scores for player 2 if ball goes off left side of screen
	if (Position.x <= 0) 
	{
		// Player 2 Point
		Start();
		Position = raylib::Vector2(GetScreenWidth() / 2, GetScreenHeight() / 2);
		Player2Score++;
	}

	// handles ball/player1 collision
	if (Position.x + 10 > Player1Pos.x && Position.x < Player1Pos.x + 10) 
	{
		if (Position.y + 10 > Player1Pos.y - 15 && Position.y < Player1Pos.y + 65 + 5) 
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

	// handles ball/player2 collision
	if (Position.x + 10 >= Player2Pos.x - 10 && Position.x < Player2Pos.x + 10)
	{
		if (Position.y + 10 > Player2Pos.y - 15 && Position.y < Player2Pos.y + 65 + 5)
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

		// makes y dir negative
		dir = raylib::Vector2(dir.x, -abs(dir.y));
	}

	// Collided with the ground
	if (Position.y >= 600)
	{
		
		if ((IsKeyDown(KEY_D) && IsKeyDown(KEY_A)) || ((IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT)))) {

		}

		// makes y dir positive
		dir = raylib::Vector2(dir.x, abs(dir.y));
	}

	Move(dir);

	
}

// checks if setting is on, if so, checks if someone is using ability
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

// checks if last player to touch ball setting is on, if so, returns true if you are the last player
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
	
	// handles colouring for Invince-Ability
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

	
	// handles player 1 winning
	if (Player1Score >= WinReq) {
		
		Player2Score = 0;

		bool time = WaitTime(3);

		if (time == true) {
			

		}
		else {
			DrawText("Player 1 Wins!", (GetScreenWidth() - MeasureText("Player 1 Wins!", 40)) / 2, 150, 40, RAYWHITE);
		}

	} // handles player 2 winning
	else if (Player2Score >= WinReq) {
		DrawText("Player 2 Wins!", (GetScreenWidth() - MeasureText("Player 2 Wins!", 40)) / 2, 150, 40, RAYWHITE);
		Player1Score = 0;

		bool time = WaitTime(3);

		if (time == true) {
			//cursedPong.gameShouldStart = false;
		}
	}
	else { // displays player scores
		DrawText(score1, 150 - MeasureText(score1, 40), 150, 40, RAYWHITE);
		DrawText(score2, GetScreenWidth() - 150 - MeasureText(score2, 40), 150, 40, RAYWHITE);
	}

}

float waitTimer = 0;
bool Ball::WaitTime(int time) { // function for waiting for time, I was getting annoyed

	waitTimer += GetFrameTime();

	if (waitTimer >= time) {
		waitTimer = 0;
		return true;
	}
	else {
		return false;
	}
}

void Ball::Move(Vector2 dir) // ball direction and speed (I know, it's bad)
{
	Position.x -= dir.x * GetFrameTime();
	Position.y -= dir.y * GetFrameTime();
}