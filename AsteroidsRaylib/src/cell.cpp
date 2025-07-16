#include "cell.hpp"

Texture2D Cell::unitTex;
Cell::Cell()
{
    unitTex = LoadTexture("Graphics/meteor_tile.png");
}

Cell::~Cell()
{
    UnloadTexture(unitTex);
}
void Cell::Draw()
{
    DrawTextureEx(unitTex, position, 0, 4, WHITE);
}
Vector2 Cell::GetUnitSize()
{
    return {float(unitTex.width*4), float(unitTex.height*4)};
}