#include <raylib.h>
#include <string>
#include "manager.hpp"
int main()
{
    int offset = 50;
    int windowWidth = GetMonitorWidth(GetCurrentMonitor());
    int windowHeight = GetMonitorHeight(GetCurrentMonitor());

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");

    SetTargetFPS(60);

    Manager manager;

    while(!WindowShouldClose()) {
        // manager.HandleInput();
        // manager.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        manager.Start();
        EndDrawing();
    }

    CloseWindow();
}