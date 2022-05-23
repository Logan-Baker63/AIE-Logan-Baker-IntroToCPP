#include "SettingInputBox.h"
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

SettingInputBox::SettingInputBox(const char* text, Vector2 position, Vector2 scale)
{
    Text = text; 
    Position = position;
    Scale = scale;
    
    name[0] = '1';
    name[1] = '2';
    TextBox = { Position.x, Position.y, Scale.x, Scale.y};
}

void SettingInputBox::Update() 
{
    if (CheckCollisionPointRec(GetMousePosition(), TextBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MaxChars))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}

void SettingInputBox::Draw()
{
    DrawText(Text, Position.x, Position.y - 20, 20, GRAY);

    DrawRectangleRec(TextBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)TextBox.x, (int)TextBox.y, (int)TextBox.width, (int)TextBox.height, RED);
    else DrawRectangleLines((int)TextBox.x, (int)TextBox.y, (int)TextBox.width, (int)TextBox.height, DARKGRAY);

    DrawText(name, (int)TextBox.x + 5, (int)TextBox.y, 30, MAROON);

    DrawText(TextFormat("%i/%i", letterCount, MaxChars), Position.x + 160, Position.y + 5, 20, DARKGRAY);

    if (mouseOnText)
    {
        if (letterCount < MaxChars)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)TextBox.x + 8 + MeasureText(name, 40), (int)TextBox.y - 2, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", Position.x + 160, Position.y + 30, 20, GRAY);
    }
}