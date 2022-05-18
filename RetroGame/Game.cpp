#include "Game.h"
#include "Player.h"
//#include <cstring>

using namespace std;

Game::Game() 
{
	defaultTex = LoadTextureFromImage(LoadImage(""));
}

void Game::Start() 
{
	Player* Player1 = new Player(defaultTex, raylib::Vector2(100, 300));
	Player* Player2 = new Player(defaultTex, raylib::Vector2(500, 300));
}

void Game::Update() 
{
	
	                                                                                                                                                                                                                                                                                                             

}