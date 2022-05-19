#pragma once
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

using namespace std;

class Ball
{
public:
	Ball(Texture2D texture, Vector2 position);
	Texture2D Texture;
	Vector2 Position;

	void Start();
	void Draw();
	void Update();
	void Move(Vector2 dir);

	Vector2 Player1Pos = raylib::Vector2(50, 225);
	Vector2 Player2Pos = raylib::Vector2(550, 225);

	int Player1Score = 0;
	int Player2Score = 0;
};

