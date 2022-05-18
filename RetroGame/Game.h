#pragma once
#include <vector>
#include "raylib.h"
#include <string>

using namespace std;

class Game
{
public:
	Game();
	void Start();
	void Update();
	Texture2D defaultTex;
};

