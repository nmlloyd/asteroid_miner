#include "star.hpp"

Star::Star()
{

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
        DrawRectangle(position.x, position.y, 2, 2, WHITE);
    // else
}
