#include <iostream>
#include <raylib.h>
#include <vector>
#include "Shope.hpp"
#include "button.hpp"

using namespace std;

Texture2D Shope::sprite = {};

Shope::Shope(){
    if(sprite.id==0){
        sprite = LoadTexture("Graphics/shop.png");
    }

    backplate = {100,100, (float) sprite.width, (float) sprite.height};

    Vector2 positionOfSellButton = {backplate.x+100, backplate.y+100};
    buttons.emplace_back(ButtonSpriteTypes::SELL, positionOfSellButton);

}