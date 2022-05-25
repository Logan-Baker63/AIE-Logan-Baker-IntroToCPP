#include "Setting.h"
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

Setting::Setting(const char* text, Vector2 position, bool onByDefault) 
{
	Text = text;
	Position = position;
	isOn = onByDefault;
}

void Setting::Draw() 
{
	DrawText(Text, Position.x, Position.y, 14, DARKGRAY);

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		if (GetMousePosition().x > Position.x && GetMousePosition().x < Position.x + OffButton.width / 3.5) {
			if (GetMousePosition().y > Position.y + 20 && GetMousePosition().y < Position.y + 20 + OffButton.height / 3) {
				if (isOn) {
					isOn = false;
				}
				else {
					isOn = true;
				}
			}
		}
	}

	if (isOn) {
		DrawTextureEx(OnButton, raylib::Vector2(Position.x, Position.y + 20), 0, 0.3, WHITE);
	}
	else {
		DrawTextureEx(OffButton, raylib::Vector2(Position.x, Position.y + 20), 0, 0.3, WHITE);
	}
}