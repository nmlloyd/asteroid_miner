#include "cell.hpp"
#include <cmath>
#include <iostream>


const int texs = 10;
Texture2D Cell::unitTex[texs] = {};
Cell::Cell()
{
    isActiveAndEnabled = true;
    for(int i = 0; i < texs; i++)
    {
        if(unitTex[i].id == 0)
        {
            switch(i)
            {
                case 0:
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_outline.png");
                    break;
                case 1:
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_center_1.png");
                    break;
                case 2:
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_center_2.png");
                    break;
                case 3:
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_gold.png");
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
                    unitTex[i] = LoadTexture("Graphics/dark_full.png");
                    break;
                case 8:
                    unitTex[i] = LoadTexture("Graphics/dark_50perc.png");
                    break;
                case 9:
                    unitTex[i] = LoadTexture("Graphics/dark_25perc.png");
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
        DrawTextureEx(unitTex[id - 1], {position.x + relativeTo.x, position.y + relativeTo.y}, 0, 4, WHITE);
        if(step != -1)//do nothing if not breaking
        {
            if(step <= 2)
            {
                DrawTextureEx(unitTex[(int)(floorf(step)+4)], {position.x + relativeTo.x, position.y + relativeTo.y}, 0, 4, WHITE);
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
        return 3;
}
void Cell::DrawOutlines()
{
    if(isActiveAndEnabled && drawOutline)
        DrawTextureEx(unitTex[0], {position.x + relativeTo.x - 8, position.y + relativeTo.y - 8}, 0, 4, WHITE);
}
Vector2 Cell::GetUnitSize()
{
    Vector2 vec = {float(unitTex[id - 1].width*4), float(unitTex[id - 1].height*4)};
        // std::cout<<vec.x<<", "<<vec.y<<std::endl;
    return vec;
}
Rectangle Cell::GetCollider()//world position
{
    return {position.x + relativeTo.x, position.y + relativeTo.y, (float)GetUnitSize().x, (float)GetUnitSize().y};
}