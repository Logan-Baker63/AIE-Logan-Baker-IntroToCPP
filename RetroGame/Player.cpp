#include "Player.h"

using namespace std;

Player::Player(Texture2D texture, Vector2 position, Color colour) // stores player information passed through a constructor
{
	Texture = texture;
	Position = position;
	Colour = colour;
}

void Player::Draw() 
{
	DrawTextureEx(Texture, Position, 0, 1, Colour); // draws player textures
}
