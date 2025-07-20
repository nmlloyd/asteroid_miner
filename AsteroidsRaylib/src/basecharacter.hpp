#pragma once
#include <raylib.h>
#include "structures.hpp"
#include "gameobject.hpp"

class BaseCharacter : public GameObject
{
    public:
        // Transform2D transform;
        // Vector2 velocity;//pixels / sec
        // Texture2D sprite;
        BaseCharacter();
        BaseCharacter(Transform2D _transform, Texture2D _sprite);
        // void Draw();
        // void Update();
        Rectangle GetCollider();
};