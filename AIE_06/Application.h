#pragma once

#include "raylib.h"

class Application
{
public:

	Application();
	~Application();

	void Run();

private:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void RotateTileColour(int tileIndex, bool random);
	void Draw();

	Color GetTileColor(int tileValue);

private:

	int m_windowWidth = 800;
	int m_windowHeight = 800;

	static const int ROWS = 80;
	static const int COLS = 80;

	int m_tiles[ROWS * COLS];

	int m_tileWidth = 10;
	int m_tileHeight = 10;
};