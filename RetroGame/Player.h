#pragma once
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

using namespace std;

class Player
{
public:
	Player(Texture2D texture, Vector2 position);
	Texture2D Texture;
	Vector2 Position;

	void Draw();

	

};

