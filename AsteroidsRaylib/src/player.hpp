#pragma once
#include <raylib.h>
#include "basecharacter.hpp"

class Player : public BaseCharacter
{
    public:
        Player();
        Player(Transform2D _transform, Texture2D _sprite);
        float speed = 9;
        double bounce = 0.2;
};