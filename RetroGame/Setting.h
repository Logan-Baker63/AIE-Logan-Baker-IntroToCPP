#pragma once
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

using namespace std;

class Setting
{

public:
	Setting(const char* text, Vector2 position, bool onByDefault);
	Texture2D OnButton = LoadTextureFromImage(LoadImage("Textures/OnButton.png"));
	Texture2D OffButton = LoadTextureFromImage(LoadImage("Textures/OffButton.png"));
	const char* Text;
	Vector2 Position;

	bool isOn = false;

	void Draw();
};

