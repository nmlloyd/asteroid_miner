#include "cell.hpp"

const int texs = 8;
Texture2D Cell::unitTex[texs] = {};
Cell::Cell()
{
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
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_center_2.png");
                    break;
                case 2:
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_center_3.png");
                    break;
                case 3:
                    unitTex[i] = LoadTexture("Graphics/meteor_tile_center_4.png");
                    break;
                case 4:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_topex.png");
                    break;
                case 5:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_btmex.png");
                    break;
                case 6:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_leftex.png");
                    break;
                case 7:
                    // unitTex[i] = LoadTexture("Graphics/meteor_tile_rightex.png");
                    break;
            }
        }
    }
}

// Cell::~Cell()
// {
//     UnloadTexture(unitTex);
// }
void Cell::Draw()
{
    DrawTextureEx(unitTex[id - 1], position, 0, 4, WHITE);
}
void Cell::DrawOutlines()
{
    DrawTextureEx(unitTex[0], {position.x - 8, position.y - 8}, 0, 4, WHITE);
}
Vector2 Cell::GetUnitSize()
{
    return {float(unitTex[id - 1].width*4), float(unitTex[id - 1].height*4)};
}
Rectangle Cell::GetCollider()
{
    return {position.x, position.y, (float)GetUnitSize().x, (float)GetUnitSize().y};
}