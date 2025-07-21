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
    CompleteMission//will show the mission below
};
enum class OreTile
{
    Putin = 4//id = 4

};
struct MiningMission//a struct for modularly adding new missions easily
{
    std::string text;
    OreTile oreToMine;
    int quantity;//amount of ore to mine
};