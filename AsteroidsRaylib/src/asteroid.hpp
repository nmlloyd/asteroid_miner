#pragma once

#include <raylib.h>
#include "cell.hpp"
#include <vector>
#include "structures.hpp"
#include "light.hpp"

class Asteroid
{
    public:
        Asteroid(Vector2 pos);
        ~Asteroid();
        void Update();
        void Draw();
        Vector2 WorldToGrid(Vector2 pixelCoords);
        Vector2 GridToWorld(Vector2 gridCoords);
        void UpdateLighting(std::vector<Light> additionalLights);
        Vector2 position;
        Vector2 gridPosition;
        unsigned int minNodes = 2;
        unsigned int maxNodes = 10;
        unsigned int minNodeRadius = 3;
        unsigned int maxNodeRadius = 10;
        Vector2 localCenterFirst;
        bool isActiveAndEnabled;
        std::vector<Cell> cells; 
        std::vector<Light> edgeLights; 
        Texture2D shading;
        Vector2 topLeftCorner;
    private:
        // std::vector<std::vector<int>> grid;
        std::vector<Vector2Bool> Generate(int r);
        void CreateRandomAsteroid(Vector2 center, int num, int min, int max);
        std::vector<Vector2Bool> MidPointCircleDraw(int xcenter, int ycenter, int r);
        std::vector<Vector2> drawcircle(int xc,int yc,int x,int y);
        bool IsInsideCircle(Vector2 point, int xcenter, int ycenter, int r);
        
        float Clamp01(double n);
        double Distance(Vector2 p1, Vector2 p2);
};