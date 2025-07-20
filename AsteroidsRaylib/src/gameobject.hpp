#pragma once
#include <raylib.h>
#include "structures.hpp"

class GameObject
{
    public:
        GameObject();
        GameObject(Transform2D _transform, Texture2D _sprite);
        Rectangle collider;
        void Draw();
        void Update();
        Transform2D transform;
        Vector2 velocity;
        Texture2D sprite;
};