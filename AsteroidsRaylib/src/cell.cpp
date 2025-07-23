#include "cell.hpp"
#include <cmath>
#include <iostream>
#include <cassert>
#include "structures.hpp"
#define NUM_OF_TEXTURES 32


Texture2D Cell::unitTex[NUM_OF_TEXTURES] = {};
Cell::Cell()
{
    isActiveAndEnabled = true;
    for(int i = 0; i < NUM_OF_TEXTURES; i++)
    {
        if(unitTex[i].id == 0)
        {
            switch(i)
            {
                case 0:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_outline.png");
                    unitTex[i] = LoadTexture("Graphics/meteorite_outline_original.png");
                    break;
                case 1:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_center_1.png");
                    unitTex[i] = LoadTexture("Graphics/meteorite_center_original_1.png");
                    break;
                case 2:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_center_2.png");
                    unitTex[i] = LoadTexture("Graphics/meteorite_center_original_2.png");
                    break;
                case 3:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_gold.png");
                    // unitTex[i] = LoadTexture("Graphics/putonium_235.png");
                    unitTex[i] = LoadTexture("Graphics/putonium_low_sat.png");
                    break;
                case 4:
                    unitTex[i] = LoadTexture("Graphics/breaking_1.png");
                    break;
                case 5:
                    unitTex[i] = LoadTexture("Graphics/breaking_2.png");
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_btmex.png");
                    break;
                case 6:
                    unitTex[i] = LoadTexture("Graphics/breaking_3.png");
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_leftex.png");
                    break;
                case 7:
                    unitTex[i] = LoadTexture("Graphics/ship_hull_outline_3.png");
                    break;
                case 8:
                    unitTex[i] = LoadTexture("Graphics/ship_hull_center.png");
                    break;
                case 9:
                    unitTex[i] = LoadTexture("Graphics/dark_25perc.png");
                    break;
                case 10:
                    unitTex[i] = LoadTexture("Graphics/empty_center.png");
                    break;
                case 11:
                    unitTex[i] = LoadTexture("Graphics/ship_hull_background.png");//outline
                    break;
                case 12:
                    unitTex[i] = LoadTexture("Graphics/computer_off.png");//decoration
                    break;
                case 13:
                    unitTex[i] = LoadTexture("Graphics/computer_on.png");//decoration
                    break;
                case 14:
                    unitTex[i] = LoadTexture("Graphics/teleporter.png");//decoration
                    break;
                case 15:
                    unitTex[i] = LoadTexture("Graphics/button.png");//decoration
                    break;
                case 16:
                    unitTex[i] = LoadTexture("Graphics/meddorite.png");//ore
                    break;
                case 17:
                    unitTex[i] = LoadTexture("Graphics/lazurite.png");//ore
                    break;
                case 18:
                    unitTex[i] = LoadTexture("Graphics/maxium.png");//ore
                    break;
                case 19:
                    unitTex[i] = LoadTexture("Graphics/lucasium.png");//trueblood
                    break;
                case 20:
                    unitTex[i] = LoadTexture("Graphics/lucasite.png");//ore
                    break;
                case 21:
                    unitTex[i] = LoadTexture("Graphics/andreasite.png");//ore
                    break;
                case 22:
                    unitTex[i] = LoadTexture("Graphics/nathanium.png");//ore
                    break;
                case 23:
                    unitTex[i] = LoadTexture("Graphics/hamza.png");//ham ore
                    break;
            }
        }
    }
}

// Cell::~Cell()
// {
//     UnloadTexture(unitTex);
// }
int Cell::Draw()
{
    if(isActiveAndEnabled)
    {
        if(id != static_cast<int>(OreTile::Putin)&&
            id != static_cast<int>(OreTile::Andreasite)&&
            id != static_cast<int>(OreTile::Nathanium)&&
            id != static_cast<int>(OreTile::Maxium)&&
            id != static_cast<int>(OreTile::Trueblood)&&
            id != static_cast<int>(OreTile::Lucasite))
        {
            DrawTextureEx(unitTex[id - 1], {position.x + relativeTo.x, position.y + relativeTo.y}, 0, 4, color);
            if(step != -1)//do nothing if not breaking
            {
                if(step <= 2)
                {
                    DrawTextureEx(unitTex[(int)(floorf(step)+4)], {position.x + relativeTo.x, position.y + relativeTo.y}, 0, 4, color);
                    return 0;
                }
                else
                {
                    isActiveAndEnabled = false;
                    return 1;
                }
            }
            else
                return 2;
        }
        else
        {
            DrawTextureEx(unitTex[id - 1], {position.x + relativeTo.x, position.y + relativeTo.y}, 0, 0.5, color);
            if(step != -1)//do nothing if not breaking
            {
                if(step <= 2)
                {
                    DrawTextureEx(unitTex[(int)(floorf(step)+4)], {position.x + relativeTo.x, position.y + relativeTo.y}, 0, 4, color);
                    return 0;
                }
                else
                {
                    isActiveAndEnabled = false;
                    return 1;
                }
            }
            else
                return 2;
        }
    }
    else    
        return 3;
}
void Cell::DrawOutlines()
{
    if(isActiveAndEnabled && drawOutline)
    {
        switch(outlineId)
        {
            case 1:
                DrawTextureEx(unitTex[0], {position.x + relativeTo.x - 8, position.y + relativeTo.y - 8}, 0, 4, color);
                break;
            case 2:
                DrawTextureEx(unitTex[7], {position.x + relativeTo.x - 8, position.y + relativeTo.y - 8}, 0, 4, color);
                break;
            case 3:
                DrawTextureEx(unitTex[11], {position.x + relativeTo.x - 8, position.y + relativeTo.y - 8}, 0, 4, color);
                break;
        }
    }
}
Vector2 Cell::GetUnitSize()
{
    //std::cout << id - 1 << std::endl;
    Vector2 vec = {float(unitTex[id - 1].width*4), float(unitTex[id - 1].height*4)};
        // std::cout<<vec.x<<", "<<vec.y<<std::endl;
    return vec;
}
Rectangle Cell::GetCollider()//world position
{
    //assert(id>=0 && id<=16);
    // std::cout<<"Cell::GetCollider() id:"<<id<<std::endl;
    if(id != 4)
        return {position.x + relativeTo.x, position.y + relativeTo.y, (float)GetUnitSize().x, (float)GetUnitSize().y};
    else
        return {position.x + relativeTo.x, position.y + relativeTo.y, (float)GetUnitSize().x/8, (float)GetUnitSize().y/8};
}