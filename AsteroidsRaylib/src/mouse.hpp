#pragma once
#include <raylib.h>

class Mouse
{
    public:
        Mouse();
        void Update();
        Vector2 GetCollider();
        Vector2 position;
};