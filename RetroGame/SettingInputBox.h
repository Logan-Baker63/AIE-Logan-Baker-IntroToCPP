#pragma once
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

class SettingInputBox
{

public:
	SettingInputBox(const char* text, Vector2 position, Vector2 scale);
	const char* Text;
	Vector2 Position;
	Vector2 Scale;

	void Update();
	void Draw();

	int MaxChars = 3;
	char name[3 + 1] = "\0";

	int letterCount = 1;

	Rectangle TextBox;
	bool mouseOnText = false;

	int framesCounter = 0;
};

