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
	float PlayerSpeed = 500;
	
	bool ballControl = false;
	bool ballControlLastPlayerOnly = false;
	bool invinceAbility = false;
	bool deflectAbility = false;

};

