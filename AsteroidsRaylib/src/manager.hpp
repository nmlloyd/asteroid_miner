#pragma once
#include <raylib.h>
#include <vector>
#include "asteroid.hpp"
#include "star.hpp"
#include "mouse.hpp"
#include "light.hpp"

class Manager
{
    public:
        Manager();
        void Draw();
        void Start();
        void Update();
    private:
        // Asteroid asteroid;
        Mouse mouse;
        Camera2D camera;
        Player player;
        int rnd = 30;
        Vector2 lastPlayerScreenPos;
        std::vector<Light> lights;
        void DestroyInactiveStars();
        void GenerateAsteroidsGrid(Vector2 positionInScreenWidths);
        // void UpdateLighting(std::vector<Light> lights, Asteroid& asteroid);
        float Clamp01(float toClamp);
        float Clamp(float min, float max, float n);
        double Distance(Vector2 p1, Vector2 p2);
        // std::vector<std::vector<Texture2D>> shading[];
        // float gridX; //= 123.0f;
        // float gridY;// = 123.0f;
        // int rx ;//= GetRandomValue(-rnd, rnd);
        // int ry ;//= GetRandomValue(-rnd, rnd);
        std::vector<Star> stars;
        std::vector<Asteroid> field;
};
