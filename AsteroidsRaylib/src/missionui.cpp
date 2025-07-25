#include "missionui.hpp"

MissionUI::MissionUI()
{
    font = LoadFont("Font/monogram.ttf");
    selectButtonUp = LoadTexture("Graphics/button_up.png");
    selectButtonDown = LoadTexture("Graphics/button_down.png");
    background = LoadTexture("Graphics/ui_bg.png");
}
void MissionUI::Draw()
{
    if(isActiveAndEnabled)
    {
        DrawTextureEx(background, {0, 0}, 0, 1, GRAY);
        if(isButtonDown)
        {
            DrawTextEx(font, "MISSION ASSIGNED\nSEE INSTRUCTIONS\n\n\n\n\n\n ENTER TO CLOSE", {(float)(GetScreenWidth() - 704/2)/2, (float)(GetScreenHeight())/2 - 220}, 40, 4, BLACK);
            DrawTextureEx(selectButtonDown, {GetButtonCollider().x, GetButtonCollider().y}, 0, uiScale, WHITE);
        }
        else
        {
            DrawTextEx(font, "PRESS FOR NEW MISSION", {(float)(GetScreenWidth() - 968/2)/2, (float)(GetScreenHeight())/2 - 180}, 40, 4, BLACK);
            DrawTextureEx(selectButtonUp, {GetButtonCollider().x, GetButtonCollider().y}, 0, uiScale, WHITE);
        }
    }
}
void MissionUI::SetButtonDown()
{
    isButtonDown = true;
}

Rectangle MissionUI::GetButtonCollider()
{
    return 
    {
        (float)(GetScreenWidth() - selectButtonUp.width*uiScale)/2, 
        (float)(GetScreenHeight() - selectButtonUp.height*uiScale)/2, 
        (float)selectButtonUp.width * uiScale / zoom, 
        (float)selectButtonUp.height * uiScale / zoom
    };
}
