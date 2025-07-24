#include <iostream>
#include <raylib.h>
#include <vector>
#include "Shope.hpp"
#include "button.hpp"

using namespace std;

Texture2D Shope::sprite = {};

Shope::Shope(Vector2 pos){
    if(sprite.id==0){
        Image img = LoadImage("Graphics/shop.png");
        ImageResizeNN(&img, GetScreenWidth()/4, GetScreenHeight()/4);
        sprite = LoadTextureFromImage(img);
    }

    backplate = {pos.x,pos.y, (float) sprite.width, (float) sprite.height};

    Vector2 positionOfSellButton = {backplate.x+50, backplate.y+50};
    buttons.emplace_back(ButtonSpriteTypes::SELL, positionOfSellButton);

    Vector2 positionOfBuyButton = {backplate.x+50, backplate.y+100};
    buttons.emplace_back(ButtonSpriteTypes::BUY, positionOfSellButton);
}

void Shope::draw(){
    DrawTexture(sprite, backplate.x, backplate.y, WHITE);

    buttons[0].draw();
    buttons[1].draw();
}