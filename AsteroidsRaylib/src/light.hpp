#pragma once

#include <raylib.h>

class Light
{
    public:
        Light();
        Light(Vector2 pos, double thresh, float r);
        Vector2 position;
        double threshold = 0;
        float radiusInPixels = 60;
};