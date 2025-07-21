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
        int outlineId = 1;
        float step = -1;
        bool isActiveAndEnabled = true;
        bool drawOutline = true;
        bool isOnEdge = true;
        bool allowCollisions = true;
        static Texture2D unitTex[16];
        Vector2 relativeTo;
};