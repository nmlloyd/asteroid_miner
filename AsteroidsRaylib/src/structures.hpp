#pragma once
#include <raylib.h>
#include <string>

struct Transform2D
{
    Vector2 position;
    float rotation;
    float scale;
};
struct ShadingPixel
{
    Vector2 position;
    float alpha = 1; // 0 to 1
};
struct Vector2Bool //a struct with a point and a boolean
{
    float x;
    float y;
    bool boolean;
};
enum class Scenes
{
    Base,
    Field
};

enum class Objective
{
    GoToComputer,//and select next mission
    BeamDown,//go to asteroid field
    CompleteMission,//will show the mission below
    ReturnToBase //return to the ship
};
enum class OreTile//maps IDs to tiles
{
    MeteorOutline = 1,
    MeteorCenter1 = 2,
    MeteorCenter2 = 3,
    Putin = 4,
    BreakingStep1 = 5,
    BreakingStep2 = 6,
    BreakingStep3 = 7,
    HullOutline = 8,
    HullCenter = 9,
    Empty = 11,
    HullBg = 12,
    ComputerOff = 13,
    ComputerOn = 14,
    Teleporter = 15,
    TeleButton = 16,

    Meddorite = 17,
    BlueOre = 18,
    Maxium = 19,
    Trueblood = 20,//lucas t
    Lucasite = 21,//the other lucas
    Andreasite = 22,
    Nathanium = 23,//just nathan
    HamOre = 24//ham
};
struct MiningMission//a struct for modularly adding new missions easily
{
    std::string text;
    OreTile oreToMine;
    int quantity;//amount of ore to mine
};

//CHANGE NUMBERS TOGETHER
const int TOTAL_NUM_OF_BUTTON_SPRITES =4;
enum class ButtonSpriteTypes{
    SELL, BUY, ITEM, UIPROMPT

};