#include "SettingInputBox.h"
#include <vector>
#include "raylib-cpp.hpp"
#include <string>

SettingInputBox::SettingInputBox(const char* text, Vector2 position, Vector2 scale) // constructor stores text input info
{
    Text = text; 
    Position = position;
    Scale = scale;
    
    // checks to set default text values (has to be updated every new input box is added unless default should be NULL)
    if (Text == "Ball Control X-Speed") {
        name[0] = '0';
    }
    else if (Text == "Ball Control Y-Speed") {
        name[0] = '6';
    }
    else if (Text == "Max Speed") {
        name[0] = '2';
        name[1] = '5';
        name[2] = '0';

        letterCount = 3;
    }
    else if (Text == "Win Requirement") {
        name[0] = '2';
        name[1] = '0';
        name[2] = NULL;

        letterCount = 2;
    }
    
    TextBox = { Position.x, Position.y, Scale.x, Scale.y}; // stores information in one variable

    /*if (val3) {
        letterCount = 3;
    }
    else {
        if (val2) {
            letterCount = 2;
        }
        else {
            if (val1) {
                letterCount = 1;
            }
            else {
                letterCount = 0;
            }
        }
    }*/


}

void SettingInputBox::Update() 
{
    if (CheckCollisionPointRec(GetMousePosition(), TextBox)) mouseOnText = true; // if mouse is on the text box
    else mouseOnText = false;

    if (mouseOnText) // if mouse is on the text box
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
    DrawText(Text, Position.x, Position.y - 20, 20, GRAY); // draws the title text above the text box

    DrawRectangleRec(TextBox, LIGHTGRAY); // draws the text box
    if (mouseOnText) DrawRectangleLines((int)TextBox.x, (int)TextBox.y, (int)TextBox.width, (int)TextBox.height, RED); // highlights the selected box
    else DrawRectangleLines((int)TextBox.x, (int)TextBox.y, (int)TextBox.width, (int)TextBox.height, DARKGRAY);

    DrawText(name, (int)TextBox.x + 5, (int)TextBox.y, 30, MAROON); // draws the text in the text box

    DrawText(TextFormat("%i/%i", letterCount, MaxChars), Position.x + 160, Position.y + 5, 20, DARKGRAY); // draws max chars for the text box

    if (mouseOnText) // handles blinking underscore
    {
        if (letterCount < MaxChars)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)TextBox.x + 8 + MeasureText(name, 40), (int)TextBox.y - 2, 40, MAROON);
        }
        else DrawText("Press BACKSPACE to delete chars...", Position.x + 160, Position.y + 30, 20, GRAY); // draws info how to remove text if you have maximum chars
    }
}