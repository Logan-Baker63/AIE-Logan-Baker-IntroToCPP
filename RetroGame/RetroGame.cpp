#include <iostream>
#include "raylib.h"
#include "Game.h"

int main()
{
    int screenWidth = 600;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Retro Game");

    SetTargetFPS(60);

    Game game;

    game.Start();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.Update();
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }
    CloseWindow();

}
