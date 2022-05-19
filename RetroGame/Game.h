#pragma once
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

using namespace std;

class Game
{
public:
	Game();
	void Start();
	void Update();

	Texture2D defaultBatTex;
	Texture2D defaultBallTex;

	void Draw();
	float PlayerSpeed = 1300;

	

};

