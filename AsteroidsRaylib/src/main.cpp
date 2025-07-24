#include <raylib.h>
#include <string>
#include <set>
#include <iostream>
#include "manager.hpp"

using namespace std;

int main()
{

    // set<Vector2> strs = {{0, 0}, {1, 1}, {2, 2}, {1, 1}};
    // // set<Vector2> strs_set(strs.begin(), strs.end());
    // for(auto& str : strs)
    // {
    //     cout << str.x << endl;
    // }


    int windowWidth =( GetMonitorWidth(GetCurrentMonitor()));
    int windowHeight = (GetMonitorHeight(GetCurrentMonitor()));

    InitWindow(windowWidth, windowHeight, "Asteroid Miner");
    InitAudioDevice();

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
    CloseAudioDevice();
}