#pragma once

#include <raylib.h>
#include "cell.hpp"
#include <vector>
#include "structures.hpp"

class Asteroid
{
    public:
        Asteroid(Vector2 pos);
        ~Asteroid();
        void Update();
        void Draw();
        Vector2 WorldToGrid(Vector2 pixelCoords);
        Vector2 GridToWorld(Vector2 gridCoords);
        Vector2 position;
        Vector2 gridPosition;
        unsigned int minNodes = 2;
        unsigned int maxNodes = 10;
        unsigned int minNodeRadius = 3;
        unsigned int maxNodeRadius = 10;
        bool isActiveAndEnabled;
        std::vector<Cell> cells; //4x4
        Texture2D shading;
        Vector2 topLeftCorner;
    private:
        // std::vector<std::vector<int>> grid;
        std::vector<Vector2> Generate(int r);
        void CreateRandomAsteroid(Vector2 center, int num, int min, int max);
        std::vector<Vector2> MidPointCircleDraw(int xcenter, int ycenter, int r);
        std::vector<Vector2> drawcircle(int xc,int yc,int x,int y);
        bool IsInsideCircle(Vector2 point, int xcenter, int ycenter, int r);
};