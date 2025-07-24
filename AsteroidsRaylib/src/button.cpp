#include "button.hpp"

Texture2D Button::sprite[TOTAL_NUM_OF_BUTTON_SPRITES] = {};

Button::Button()
{
    
    // sprite[ButtonSpriteTypes::UIPROMPT]=LoadTexture("Graphics/UIButton.png");
    // buttonArea={100,100,(float) sprite[ButtonSpriteTypes::UIPROMPT].width,(float) sprite[ButtonSpriteTypes::UIPROMPT].height};
}

Button::Button(ButtonSpriteTypes spriteIDIn, Vector2 postion){
    spriteID = spriteIDIn; //Save Sprite ID

    //If not save (i.e. sprite id at position id of array is equalled to zero) then it will load it in
    if(sprite[static_cast<int> (spriteIDIn)].id == 0){
        switch(spriteIDIn){
            case ButtonSpriteTypes::SELL:
                sprite[static_cast<int> (ButtonSpriteTypes::SELL)] = LoadTexture("Graphics/sell.png");
                break;
            case ButtonSpriteTypes::BUY:
                sprite[static_cast<int> (ButtonSpriteTypes::BUY)] = LoadTexture("Graphics/buy.png");
                break;
            case ButtonSpriteTypes::ITEM:
                sprite[static_cast<int> (ButtonSpriteTypes::ITEM)] = LoadTexture("Graphics/item.png");
                break;
            case ButtonSpriteTypes::UIPROMPT:
                sprite[static_cast<int> (ButtonSpriteTypes::UIPROMPT)] = LoadTexture("Graphics/UIButton.png");
                break;
        }
    }

    //Assign correct Button area based on sprite
    buttonArea={postion.x, postion.y, 
        (float) sprite[static_cast<int> (spriteIDIn)].width, (float) sprite[static_cast<int> (spriteIDIn)].height};
    
}

int Button::getSpriteIndex(){
    return static_cast<int> (spriteID);
}

void Button::draw()
{
    DrawTextureEx(sprite[getSpriteIndex()], {buttonArea.x,buttonArea.y}, 0, 2, WHITE);
}

void setup(){

}

Rectangle Button::getButtonArea(){
    return buttonArea;
}
