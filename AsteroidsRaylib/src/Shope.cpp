#include <iostream>
#include <raylib.h>
#include <vector>
#include "Shope.hpp"
#include "button.hpp"

using namespace std;

Texture2D Shope::sprite = {};

Shope::Shope(){
    if(sprite.id==0){
        Image img = LoadImage("Graphics/shop.png");
        ImageResizeNN(&img, GetScreenWidth()/4, GetScreenHeight()/4);
        sprite = LoadTextureFromImage(img);
    }

    backplate = {(float)GetScreenWidth()/2-sprite.width/2-300,(float)GetScreenHeight()/2-sprite.height/2-200, (float) sprite.width, (float) sprite.height};

    // Vector2 positionOfSellButton = {backplate.x+50, backplate.y+50};
    // buttons.emplace_back(ButtonSpriteTypes::SELL, positionOfSellButton);

    // Vector2 positionOfBuyButton = {backplate.x+50, backplate.y+100};
    // buttons.emplace_back(ButtonSpriteTypes::BUY, positionOfSellButton);

    Vector2 positionOfPickaxe1 = {backplate.x+50, backplate.y+150};
    buttons.emplace_back(ButtonSpriteTypes::UIPROMPT, positionOfPickaxe1, "Wilbur Pickaxe. press 4. $100", RED);

    Vector2 positionOfPickaxe2 = {backplate.x+50, backplate.y+250};
    buttons.emplace_back(ButtonSpriteTypes::UIPROMPT, positionOfPickaxe2, "Graphene Pickaxe. press 3. $70", PINK);

    Vector2 positionOfPickaxe3 = {backplate.x+50, backplate.y+350};
    buttons.emplace_back(ButtonSpriteTypes::UIPROMPT, positionOfPickaxe3, "Wolfram Pickaxe. press 2. $30", GREEN);

    Vector2 positionOfPickaxe4 = {backplate.x+50, backplate.y+450};
    buttons.emplace_back(ButtonSpriteTypes::UIPROMPT, positionOfPickaxe4, "Stone Pickaxe. press 1. $0.0", WHITE);

    isOpen=false;
}

void Shope::draw(){
    if(isOpen){
        DrawTextureEx(sprite, {backplate.x, backplate.y}, 0, 2, WHITE);

        // buttons[0].draw();
        // buttons[1].draw();
        for(auto button: buttons){
            button.draw();
        }
    }
}

bool Shope::getOverlayState()
{
    return isOpen;
}

void Shope::setShop(bool state)
{
    isOpen = state;
}

void Shope::toggleShop()
{
    isOpen = !isOpen;
}
