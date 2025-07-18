#pragma once
#include <raylib.h>

struct Transform2D
{
    Vector2 position;
    float rotation;
    float scale;
};
struct ShadingPixel
{
    Vector2 position;
    float alpha = 1; // 0 to 1
};
struct Vector2Bool //a struct with a point and a boolean
{
    float x;
    float y;
    bool boolean;
};