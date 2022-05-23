#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "Setting.h"
#include "SettingInputBox.h"

int main()
{
    int screenWidth = 600;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetWindowIcon(LoadImage("Textures/PongIcon.png"));

    

    SetTargetFPS(60);


    Setting* ballControl = new Setting("Ball Control", raylib::Vector2(20, 20));
    Setting* ballControlLastPlayerOnly = new Setting("only last player to touch ball", raylib::Vector2(200, 20));
    Setting* invinceAbility = new Setting("Invince-ability", raylib::Vector2(20, 80));
    Setting* deflectAbility = new Setting("Deflect ability", raylib::Vector2(20, 140));

    SettingInputBox* ySpeed = new SettingInputBox("Ball Control Y-Speed", raylib::Vector2(20, 220), raylib::Vector2(150, 30));
    SettingInputBox* xSpeed = new SettingInputBox("Ball Control X-Speed", raylib::Vector2(20, 300), raylib::Vector2(150, 30));

    Game game;

    bool gameShouldStart = false;

    //game.Start();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        if (gameShouldStart) {
            game.Update();

            BeginDrawing();

            ClearBackground(GRAY);

            game.Draw();

            EndDrawing();
        }
        else {
            ySpeed->Update();
            xSpeed->Update();
            
            BeginDrawing();

            ClearBackground(GRAY);

            DrawRectangle(10, 10, 580, 580, LIGHTGRAY);

            ballControl->Draw();
            ballControlLastPlayerOnly->Draw();
            invinceAbility->Draw();
            deflectAbility->Draw();
            ySpeed->Draw();
            xSpeed->Draw();

            DrawRectangle(200, 500, 200, 80, GRAY);
            DrawText("Start", 235, 520, 46, DARKGRAY);

            EndDrawing();

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (GetMousePosition().x > 200 && GetMousePosition().x < 200 + 200) {
                    if (GetMousePosition().y > 500 && GetMousePosition().y < 500 + 80) {
                        game.ballControl = ballControl->isOn;
                        game.ballControlLastPlayerOnly = ballControlLastPlayerOnly->isOn;
                        game.invinceAbility = invinceAbility->isOn;
                        game.deflectAbility = deflectAbility->isOn;
                        
                        game.Start();
                        gameShouldStart = true;
                    }
                }
            }

        }
        
    }
    CloseWindow();

}
