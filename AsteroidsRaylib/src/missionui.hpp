#include "structures.hpp"
#include <raylib.h>

class MissionUI
{
    public:
        MissionUI();
        void Draw();
        Rectangle GetButtonCollider();
        void SetButtonDown();

        bool isActiveAndEnabled = false;
        bool isButtonDown = false;
        MiningMission randomizedMission;
        float uiScale = 6;
    private:
        Font font;
        Texture2D selectButtonUp;
        Texture2D selectButtonDown;
        Texture2D background;
};