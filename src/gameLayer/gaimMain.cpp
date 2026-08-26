#include <fstream>
#include <raylib.h>
#include "gameMain.h"

bool initGame()
{
    return true;
}

bool updateGame(Font roboto, int scaledFontSize)
{
    Color c;
    c.r = 255;
    c.g = 0;
    c.b = 200;
    c.a = 255;
    
    Vector2 textPos = { 40.0f, 40.0f };
    DrawTextEx(roboto, "Congrats! You created your first window!", textPos, (float)scaledFontSize, 1.0f, c);

    // other gameplay stuff

    if (IsKeyPressed(KEY_A))
    {
        // ...
    }

    return true;
}

void closeGame()
{
    std::ofstream f("resources/log.txt", std::ios::app);
    f << "\nCLOSED\n";
    f.close();
}