#include "Application.h"
#include "raylib.h"
#include <stdlib.h>
#include <algorithm>

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "Simple Tilemap");
	SetTargetFPS(60);

	Load();

	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}

	Unload();
}

void Application::Load()
{
	// Task1:
	// Initialise all values in m_tiles array to a random
	// value between 0 and 5 exclusive;
	// -----------------------------------------------------
	
	for (int i = 0; i < ROWS * COLS; i++) {
		m_tiles[i] = std::rand() % 5;
	}
	

	// -----------------------------------------------------
}

void Application::Unload()
{

}

void Application::Update(float deltaTime)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePos = GetMousePosition();

		// Task 3:
		// TODO: Calculate row and col index based on the mouse positon

		int rowIndex = mousePos.x / m_tileHeight;

		int colIndex = mousePos.y / m_tileWidth;

		// TODO: calculate the index of the tile clicked on based on the row/col index
		int tileIndex = (rowIndex * COLS) + colIndex;
		
		RotateTileColour(tileIndex, false);
	}
	
	//static effect
	/*for (int i = 0; i < 2500; i++) {
		RotateTileColour(std::rand() % (ROWS * COLS), true);
	}*/
	
}

void Application::RotateTileColour(int tileIndex, bool random) {
	
	if (!random) {
		m_tiles[tileIndex] += 1;
		if (m_tiles[tileIndex] >= 5)
			m_tiles[tileIndex] = 0;
	}
	else {
		m_tiles[tileIndex] = std::rand() % 5;
	}
	
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	// Task2:
	// use a nested loop to iterate over rows and columns
	// Use raylib's DrawRect method to draw each tile in the array.
	// 	   use the row and col index multipled by m_tileHeight/m_tileWidth
	// 	   to calculate the x and y position for each rectangle.
	// 
	// change the color of the rect drawn based on the value of the tile.
	// 	   We have created a helper function you can use "GetTileColor"
	// --------------------------------------------------------------------
	// write your code here
	float xPos = 0;
	float yPos = 0;

	for (int r = 0; r < ROWS; r++) {
		xPos = r * m_tileHeight;
		for (int c = 0; c < COLS; c++) {
			yPos = c * m_tileWidth;

			Color color = GetTileColor(m_tiles[(r * COLS) + c]); // pass in the tilevalue

			DrawRectangle(xPos, yPos, m_tileWidth, m_tileHeight, color);
		}
	}

	 

	

	// --------------------------------------------------------------------

	EndDrawing();
}

Color Application::GetTileColor(int tileValue)
{
	switch (tileValue)
	{
	case 0: return WHITE;
	case 1: return LIGHTGRAY;
	case 2: return WHITE;
	case 3: return LIGHTGRAY;
	case 4: return GRAY;
	}
	
	return BLACK;
}