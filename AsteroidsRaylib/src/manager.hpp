#pragma once
#include <raylib.h>
#include <vector>
#include "asteroid.hpp"
#include "star.hpp"
#include "mouse.hpp"
#include "light.hpp"
#include <string>
#include "missionui.hpp"
#include "button.hpp"

class Manager
{
    public:
        Manager();
        void Draw();
        void Start();
        void Update();
    private:
        bool continueLoop = true;
        bool showDebug = false;
        bool showTeleportAnim = false;
        Mouse mouse;
        Camera2D camera;
        Player player;
        int rnd = 30;
        Scenes scene = Scenes::Base;
        Vector2 lastPlayerScreenPos;
        std::vector<Light> lights;
        void ToggleComputerScreen();
        void DestroyInactiveStars();
        void GenerateAsteroidsGrid(Vector2 positionInScreenWidths);
        void ChangeScene(Scenes sceneId);
        void LoadSceneBase();
        void LoadSceneField(Vector2 playerScreenPos, bool erase);
        void SetRandomMission();
        std::vector<Cell> LoadStructureFromFile(std::string fileName);
        // void UpdateLighting(std::vector<Light> lights, Asteroid& asteroid);
        float Clamp01(float toClamp);
        float Clamp(float min, float max, float n);
        double Distance(Vector2 p1, Vector2 p2);
        std::vector<Star> stars;
        std::vector<Asteroid> field;
        std::vector<std::string> debugConsole;
        Font font;
        Objective objective;
        MiningMission mission;
        MissionUI computerUI;
        float lastMineTime = 0;
        float currMineTime;
        float mineCooldown = 0.25f;//in seconds
        float mineSpeed = 1;
        int startAnimTime;//time of animation start in frames
        int animPlateauTime = 120;//time before fade in frames
        int animFadeTime = 100;//time to fade in frames

        
};
