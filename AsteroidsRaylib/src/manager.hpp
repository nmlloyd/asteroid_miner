#pragma once
#include <raylib.h>
#include <vector>
#include "asteroid.hpp"
#include "star.hpp"
#include "mouse.hpp"

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
        void DestroyInactiveStars();
        void GenerateAsteroidsGrid(Vector2 positionInScreenWidths);
        // float gridX; //= 123.0f;
        // float gridY;// = 123.0f;
        // int rx ;//= GetRandomValue(-rnd, rnd);
        // int ry ;//= GetRandomValue(-rnd, rnd);
        std::vector<Star> stars;
        std::vector<Asteroid> field;
};
