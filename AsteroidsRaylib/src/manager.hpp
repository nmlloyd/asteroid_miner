#pragma once
#include <raylib.h>
#include <vector>
#include "asteroid.hpp"
#include "star.hpp"
#include "mouse.hpp"
#include "light.hpp"
#include <string>

class Manager
{
    public:
        Manager();
        void Draw();
        void Start();
        void Update();
    private:
        bool showDebug = false;
        Mouse mouse;
        Camera2D camera;
        Player player;
        int rnd = 30;
        int scene = 1;
        Vector2 lastPlayerScreenPos;
        std::vector<Light> lights;
        void DestroyInactiveStars();
        void GenerateAsteroidsGrid(Vector2 positionInScreenWidths);
        void ChangeScene(int sceneId);
        std::vector<Cell> LoadStructureFromFile(std::string fileName);
        // void UpdateLighting(std::vector<Light> lights, Asteroid& asteroid);
        float Clamp01(float toClamp);
        float Clamp(float min, float max, float n);
        double Distance(Vector2 p1, Vector2 p2);
        std::vector<Star> stars;
        std::vector<Asteroid> field;
};
