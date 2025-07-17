#include "star.hpp"

Star::Star()
{
    size = GetRandomValue(0, 2);
}

// void Star::DestroyInactiveStars()
// {

// }
void Star::Update()
{
    if(isActive)
    {
        if(position.x > player.transform.position.x + (GetScreenWidth() + player.sprite.width)/2)//offscreen right side
        {
            isActive = false;
        }
        else if(position.x < player.transform.position.x - (GetScreenWidth() + player.sprite.width)/2)//offscreen left side
        {
            isActive = false;
        }

        if(position.y > player.transform.position.y + (GetScreenHeight() + player.sprite.height)/2)//offscreen up
        {
            isActive = false;
        }
        else if(position.y < player.transform.position.y - (GetScreenHeight() + player.sprite.height)/2)//offscreen up
        {
            isActive = false;
        }
    }
}
void Star::Draw()
{
    if(isActive)
    {
        if(size == 0)//half-transparent
            DrawRectangle(position.x, position.y, 1, 1, {255, 255, 255, 127});
        else
            DrawRectangle(position.x, position.y, size, size, WHITE);
    }
    // else
}
