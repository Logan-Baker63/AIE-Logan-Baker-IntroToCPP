#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "Setting.h"
#include "SettingInputBox.h"
//#include "CursedPong.h"

int main()
{
    int screenWidth = 1000;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Cursed Pong");
    SetWindowIcon(LoadImage("Textures/PongIcon.png"));

    

    SetTargetFPS(60);

    // creates buttons
    Setting* ballControl = new Setting("Ball Control", raylib::Vector2(20, 20), true);
    Setting* ballControlLastPlayerOnly = new Setting("only last player to touch ball", raylib::Vector2(200, 20), false);
    Setting* invinceAbility = new Setting("Invince-ability", raylib::Vector2(20, 80), true);
    Setting* deflectAbility = new Setting("Deflect ability", raylib::Vector2(20, 140), true);

    SettingInputBox* ySpeed = new SettingInputBox("Ball Control Y-Speed", raylib::Vector2(20, 220), raylib::Vector2(150, 30));
    SettingInputBox* xSpeed = new SettingInputBox("Ball Control X-Speed", raylib::Vector2(20, 300), raylib::Vector2(150, 30));
    SettingInputBox* angleLimit = new SettingInputBox("Max Speed", raylib::Vector2(20, 380), raylib::Vector2(150, 30));
    SettingInputBox* winAmount = new SettingInputBox("Win Requirement", raylib::Vector2(20, 460), raylib::Vector2(150, 30));

    Game game;

    bool gameShouldStart = false;
    bool gameShouldEnd = false;

    //game.Start();

    // Main game loop
    while (!gameShouldEnd)    // Detect window close button or ESC key
    {
        
        if (gameShouldStart) { // if start button is pressed
            game.Update();

            BeginDrawing();

            ClearBackground(GRAY);

            game.Draw();

            EndDrawing();
        }
        else { // if ESC is pressed or program just opened (in future if someone wins too)
            ySpeed->Update();
            xSpeed->Update();
            angleLimit->Update();
            winAmount->Update();

            BeginDrawing();

            ClearBackground(GRAY); // set bg border colour

            DrawRectangle(10, 10, 980, 580, LIGHTGRAY); // set bg colour

            ballControl->Draw(); // draws all game objects
            ballControlLastPlayerOnly->Draw();
            invinceAbility->Draw();
            deflectAbility->Draw();
            ySpeed->Draw();
            xSpeed->Draw();
            angleLimit->Draw();
            winAmount->Draw();

            DrawRectangle(100, 500, 200, 80, GRAY); // start button
            DrawText("Start", 135, 520, 46, DARKGRAY);

            DrawRectangle(400, 500, 200, 80, GRAY); // reset to default button
            DrawText("Reset", 435, 520, 46, DARKGRAY);

            DrawRectangle(GetScreenWidth() - 100 - 200, GetScreenHeight() - 100, 200, 80, GRAY); // quit button
            DrawText("Quit", GetScreenWidth() - 100 - 200 + 35, GetScreenHeight() - 100 + 20, 46, DARKGRAY);

            EndDrawing();

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) // on click
            {
                if (GetMousePosition().x > 400 && GetMousePosition().x < 400 + 200) { // if reset to defaults button is pressed
                    if (GetMousePosition().y > 500 && GetMousePosition().y < 500 + 80) {
                        ballControl->isOn = true; 
                        ballControlLastPlayerOnly->isOn = false;
                        invinceAbility->isOn = true;
                        deflectAbility->isOn = true;

                        xSpeed->name[0] = '0';
                        xSpeed->name[1] = NULL;
                        xSpeed->name[2] = NULL;
                        xSpeed->letterCount = 1;

                        ySpeed->name[0] = '6';
                        ySpeed->name[1] = NULL;
                        ySpeed->name[2] = NULL;
                        ySpeed->letterCount = 1;

                        angleLimit->name[0] = '2';
                        angleLimit->name[1] = '5';
                        angleLimit->name[2] = '0';
                        angleLimit->letterCount = 3;

                        winAmount->name[0] = '2';
                        winAmount->name[1] = '0';
                        winAmount->name[2] = NULL;
                        winAmount->letterCount = 2;
                    }
                }
                // ends program if quit button is pressed
                if (GetMousePosition().x > GetScreenWidth() - 300 && GetMousePosition().x < GetScreenWidth() - 300 + 200) {
                    if (GetMousePosition().y > GetScreenHeight() - 100 && GetMousePosition().y < GetScreenHeight() - 100 + 80) {
                        gameShouldEnd = true;
                    }
                }

                // starts the game when start is pressed
                if (GetMousePosition().x > 100 && GetMousePosition().x < 100 + 200) {
                    if (GetMousePosition().y > 500 && GetMousePosition().y < 500 + 80) {
                        // updates script values according to settings
                        
                        game.ballControl = ballControl->isOn;
                        game.ballControlLastPlayerOnly = ballControlLastPlayerOnly->isOn;
                        game.invinceAbility = invinceAbility->isOn;
                        game.deflectAbility = deflectAbility->isOn;

                        game.xSpeed = game.charArrayToInt(xSpeed->name);
                        game.ySpeed = game.charArrayToInt(ySpeed->name);
                        game.angleLimit = game.charArrayToInt(angleLimit->name);
                        game.winReq = game.charArrayToInt(winAmount->name);

                        game.Start();
                        gameShouldStart = true;
                    }
                }
            }

            

        }
        
        // // exit to main settings menu
        if (WindowShouldClose()) {
            gameShouldStart = false;
        }

    }
    CloseWindow();

    return 0;
}
