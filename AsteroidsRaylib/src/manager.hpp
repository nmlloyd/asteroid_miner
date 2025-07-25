#pragma once
#include <raylib.h>
#include <vector>
#include "asteroid.hpp"
#include "star.hpp"
#include "mouse.hpp"
#include "light.hpp"
#include <string>
#include "missionui.hpp"
#include "Shope.hpp"

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
        bool canMine = true;
        bool jumpscare = false;
        bool movedThisFrame = false;
        bool isFreeCam = false;
        bool reflectedThisFrame = false;

        bool allowEpic = false;
        bool allowLegendary = false;
        bool allowWilbur = false;

        int frameCounter = 0;
        int frameDelay = 3;
        int currentAnimFrame = 0;
        unsigned int nextFrameDataOffset = 0;

        float debugSize = 4;

        Music main_music;
        Music music;
        Music staticMusic;
        Mouse mouse;
        Texture2D noise;
        Animator widePutinWalkingAnim;
        Camera2D camera;
        Player player;
        int rnd = 30;
        int voidDist = 8;
        Vector2 playerScreenPos;
        Vector2 debugPosition; //multipurpose position
        Scenes scene = Scenes::Base;
        Vector2 lastPlayerScreenPos;
        std::vector<Light> lights;
        void CheckCollisionCells();
        void HandleSpookyScary();
        void HandleInput();
        void CheckUIButton();
        void HandlePlayerVelocity();
        void CheckCellCollisionLoops();
        void ToggleComputerScreen();
        void GenerateAsteroidsGrid(Vector2 positionInScreenWidths);
        void ChangeScene(Scenes sceneId);
        void LoadSceneBase();
        void LoadSceneField(Vector2 playerScreenPos, bool erase);
        void SetRandomMission();

        //local update funcs
        void runShopUI();

        //local draw funcs
        void DrawDebugColls();
        void DrawAsteroidField();
        void DrawStarsBackground();
        void DrawTeleportAnimationFromTime();
        void SwitchObjectiveAndDraw();
        void SwitchPickaxeAndDraw();
        void DrawMouseCursor();

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
        float mineSpeed = 0.3333f;//(1/mineSpeed) * 3 = clicks to break ore
        int startAnimTime;//time of animation start in frames
        int animPlateauTime = 80;//time before fade in frames
        int animFadeTime = 100;//time to fade in frames
        float maxMineDist = 8;//in tiles
        std::vector<Pickaxe> pickaxes;
        int Money =0;
        Shope shop;
};
