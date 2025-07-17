#include "asteroid.hpp"
#include <iostream>
#include <cmath>
using namespace std;
Asteroid::Asteroid(Vector2 pos)
{
    // Vector2 center = {-8, -8};
    isActiveAndEnabled = true;
    position = pos;
    CreateRandomAsteroid(position, GetRandomValue(minNodes, maxNodes), minNodeRadius, maxNodeRadius);
    // Vector2 centerMain = {-8, -8};
    // vector<Vector2> vecs = Generate(GetRandomValue(1, 4)*2 + 1);
    // for(int i = 0; i < vecs.size(); i++)
    // {
    //     Vector2 vec = vecs[i];
    //     Cell cell = Cell();
    //     cell.position = {GetScreenWidth()/2 + (cell.GetUnitSize().x * (vec.x + centerMain.x)), GetScreenHeight()/2 + (cell.GetUnitSize().y * (vec.y + centerMain.y))};
    //     cell.id = GetRandomValue(2, 4);//random center
    //     int rnd = GetRandomValue(0, 16);
    //     if(rnd == 7)
    //     {
    //         cell.id = 5;
    //     }
    //     cells.push_back(cell);
    // }
}

Asteroid::~Asteroid()
{
    
}

void Asteroid::Update()
{

}
void Asteroid::Draw()
{
    for(auto& cell : cells)
    {
        cell.DrawOutlines();
    }
    for(auto& cell : cells)
    {
        cell.Draw();
    }
    for(auto& cell : darkCells100)
    {
        cell.Draw();
    }
}
bool Asteroid::IsInsideCircle(Vector2 point, int xcenter, int ycenter, int r)
{
    return (pow(point.x - xcenter, 2) + pow(point.y - ycenter, 2)) < pow(r, 2);
}

vector<Vector2> Asteroid::Generate(int r)
{
    int radius = r;
    int d = 2*radius;
    Vector2 center = {radius, radius};
    vector<Vector2> circle = MidPointCircleDraw(center.x, center.y, radius);
    vector<Vector2> filledCircle = circle;
    for(float y = 0; y < d; y++)
    { 
        for(float x = 0; x < d; x++)
        {
            if(IsInsideCircle({x, y}, center.x, center.y, radius))
            {
                bool isNotCopy = true;
                for(Vector2& vec : circle)
                {
                    if(vec.x == x && vec.y == y)//is a copy
                    {
                        isNotCopy = false;
                        break;
                    }
                }
                if(isNotCopy)
                    filledCircle.push_back({x,y});
            }
        }
    }
    return filledCircle;
}

vector<Vector2> Asteroid::drawcircle(int xcenter, int ycenter, int x, int y){
    vector<Vector2> circ;
    circ.push_back({(float)(xcenter+x), (float)(ycenter+y)});
    circ.push_back({(float)(xcenter-x), (float)(ycenter+y)});
    circ.push_back({(float)(xcenter+x), (float)(ycenter-y)});
    circ.push_back({(float)(xcenter-x), (float)(ycenter-y)});
    circ.push_back({(float)(xcenter+y), (float)(ycenter+x)});
    circ.push_back({(float)(xcenter-y), (float)(ycenter+x)});
    circ.push_back({(float)(xcenter+y), (float)(ycenter-x)});
    circ.push_back({(float)(xcenter-y), (float)(ycenter-x)});
    // putpixel(xcenter+y, ycenter+x, WHITE);
    // putpixel(xcenter-y, ycenter+x, WHITE);
    // putpixel(xcenter+y, ycenter-x, WHITE);
    // putpixel(xcenter-y, ycenter-x, WHITE);
    return circ;
}
vector<Vector2> Asteroid::MidPointCircleDraw(int xcenter, int ycenter, int radius){
    vector<Vector2> circle;

    int x = 0;
    int y = radius;
    int p = 1 - radius;
    vector<Vector2> c1 = drawcircle(xcenter, ycenter, x, y);
    for (Vector2& vec2 : c1)
    {
        circle.push_back(vec2);
    }
    while(x<y){
       x++;
       if(p<0){
            p = p + 2*x + 1;
       }
       else{
            y--;
            p = p + 2*(x-y) + 1;
       }
       vector<Vector2> circlePart = drawcircle(xcenter, ycenter, x, y);
       for (Vector2& vec2 : circlePart)
       {
           circle.push_back(vec2);
       }
    }
    return circle;
 }
 
void Asteroid::CreateRandomAsteroid(Vector2 centerMain, int maxAsteroids, int min, int max)
{
    int lastRad = -1;
    Vector2 localCenter = {0, 0};
    float randomRadiusPrev = 0;
    for(int i = 0; i < maxAsteroids + 1; i++)
    {
        float randomRadius = GetRandomValue(min,max);
        int randomDirection;
        if(i != 0)
            randomDirection = GetRandomValue(0,5)%4;
        else
            randomDirection = 4;

        if(randomDirection == lastRad)
        {
            while(randomDirection == lastRad)
            {
                randomDirection = GetRandomValue(0,5)%4;
            }
        }

        // float sub = floorf(max/2);
        switch (randomDirection)
        {
            case 0://right
                localCenter.x += randomRadiusPrev ;//+ randomRadius - sub;
                break;
            case 1://left
                localCenter.x -= randomRadiusPrev ;//+ randomRadius - sub;
                break;
            case 2://up
                localCenter.y += randomRadiusPrev ;//+ randomRadius - sub;
                break;
            case 3://down
                localCenter.y -= randomRadiusPrev ;//+ randomRadius - sub;
                break;
            default:
                break;
        }
        vector<Vector2> vecs = Generate(randomRadius);
        // vector<Vector2> outline1 = MidPointCircleDraw(randomRadius, randomRadius, randomRadius);
        // vector<Vector2> dark50; //= Generate(randomRadius);
        // for(auto& vec : vecs)
        // {
        // }
        
        

        for(int i = 0; i < vecs.size(); i++)
        {
            vector<Vector2> outline1 = MidPointCircleDraw(randomRadius, randomRadius, randomRadius);
            Vector2 vec = vecs[i];
            Cell cell = Cell();
            cell.position = {GetScreenWidth()/2 + (cell.GetUnitSize().x * (vec.x + localCenter.x) + centerMain.x ), GetScreenHeight()/2 + (cell.GetUnitSize().y * (vec.y + localCenter.y) + centerMain.y)};
            
            cell.id = GetRandomValue(2, 3);//random center
            int rnd = GetRandomValue(0, 32);
            if(rnd == 7)
            {
                cell.id = 4;
            }
            
            // bool isNotOutline = true;
            // for(Vector2& vec_ : outline1)
            // {
            //     Vector2 newVec = {GetScreenWidth()/2 + (cell.GetUnitSize().x * (vec_.x + localCenter.x) + centerMain.x ), GetScreenHeight()/2 + (cell.GetUnitSize().y * (vec_.y + localCenter.y) + centerMain.y)};
            //     if(newVec.x == cell.position.x && newVec.y == cell.position.y)//is an outline
            //     {
            //         isNotOutline = false;
            //     }
            // }

            // if(isNotOutline)
            // {
            //     cells.push_back(cell);
            //     cell.id = 9;
            //     darkCells100.push_back(cell);
            // }
            // else
            // {
            //     cells.push_back(cell);
            // }
            cells.push_back(cell);
        }
        switch (randomDirection)
        {
            case 0://right
                lastRad = 1;
                break;
            case 1://left
                lastRad = 0;
                break;
            case 2://up
                lastRad = 3;
                break;
            case 3://down
                lastRad = 2;
                break;
            default:
                break;
        }
        randomRadiusPrev = randomRadius;
    }
}

Vector2 Asteroid::WorldToGrid(Vector2 pixelCoords)
{
    return {pixelCoords.x / 12, pixelCoords.y / 12};
}
Vector2 Asteroid::GridToWorld(Vector2 gridCoords)
{
    return {gridCoords.x * 12, gridCoords.y * 12};
}