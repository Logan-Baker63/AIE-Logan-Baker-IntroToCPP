#include "Player.h"

using namespace std;

Player::Player(Texture2D texture, Vector2 position) 
{
	Texture = texture;
	Position = position;
}

void Player::Draw() 
{
	DrawTextureEx(Texture, Position, 0, 1, WHITE);
}
