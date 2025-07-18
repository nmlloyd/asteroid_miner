#pragma once
#include <raylib.h>

class Cell
{
    public:
        Cell();
        //~Cell();
        int Draw();
        void DrawOutlines();
        Vector2 GetUnitSize();
        Rectangle GetCollider();
        Vector2 position;//local position, relative to asteroid
        int id = 2;
        float step = -1;
        bool isActiveAndEnabled = true;
        bool drawOutline = true;
        bool isOnEdge = true;
        static Texture2D unitTex[10];
        Vector2 relativeTo;
};