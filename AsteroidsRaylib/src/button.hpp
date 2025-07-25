#pragma once
#include "raylib.h"
#include <string>
#include "structures.hpp"

using namespace std;





class Button{
    private:
    static Texture2D sprite[TOTAL_NUM_OF_BUTTON_SPRITES];
    ButtonSpriteTypes spriteID;
    Rectangle buttonArea;
    string buttonText;
    Color textColor;
    int getSpriteIndex();

    public:
    Button();
    Button(ButtonSpriteTypes spriteIDIn, Vector2 position);
    Button(ButtonSpriteTypes spriteIDIn, Vector2 position, string buttonTextIn, Color textColorIn);
    void draw();
    void setup();
    Rectangle getButtonArea();
    bool isInsideButton(Vector2 mosPos);

};

//Button b1 = Button(...)
//b1.draw();