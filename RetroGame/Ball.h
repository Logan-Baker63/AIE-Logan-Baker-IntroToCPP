#pragma once
#include <vector>
#include "raylib-cpp.hpp"
#include <string>
//#include "Game.h"

using namespace std;

class Ball
{
public:
	Ball(Texture2D texture, Vector2 position, Color colour, bool ballControl, bool ballControlLastPlayerOnly, bool invinceAbility, int xSpeed, int ySpeed, int speedLimit, int winReq);
	Texture2D Texture;
	Vector2 Position;
	Color Colour;
	int xSpeed;
	int ySpeed;
	int SpeedLimit;
	int WinReq = 20;

	Vector2 dir = raylib::Vector2(0, 0);

	void Start();
	void Draw();
	void Update();
	void Move(Vector2 dir);
	bool WaitTime(int time);

	Vector2 Player1Pos = raylib::Vector2(50, 225);
	Vector2 Player2Pos = raylib::Vector2(950, 225);

	int Player1Score = 0;
	int Player2Score = 0;

	bool hitInvert1 = false;
	bool hitInvert2 = false;

	bool isSlow = true;

	int lastPlayer = 0;

	bool ballControl = false;
	bool ballControlLastPlayerOnly = false;
	bool invinceAbility = false;

	bool InvinceAbilityCheck();
	bool LastPlayerTouchBall(int player);
};

