#pragma once
#include <raylib.h>
#include "basecharacter.hpp"
#include "structures.hpp"

class Player : public BaseCharacter
{
    public:
        Player();
        Player(Transform2D _transform, Texture2D _sprite);
        float speed = 13;
        double bounce = 0.2;//0.2;
        PickaxeType pickaxe = PickaxeType::Default;
};