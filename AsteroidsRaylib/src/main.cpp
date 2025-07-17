#include <raylib.h>
#include <string>
#include "manager.hpp"


int main()
{
    int windowWidth = GetMonitorWidth(GetCurrentMonitor());
    int windowHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(windowWidth, windowHeight, "Asteroid Miner");

    SetTargetFPS(60);

    Manager manager;
    manager.Start();

    while(!WindowShouldClose()) {
        HideCursor();
        manager.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        manager.Draw();
        // DrawRectangle(1255, 656, 100, 100, WHITE);
        EndDrawing();
    }

    CloseWindow();
}