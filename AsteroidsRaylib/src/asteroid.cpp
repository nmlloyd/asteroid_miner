#include "asteroid.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "gameobject.hpp"

using namespace std;
Asteroid::Asteroid()
{
    isActiveAndEnabled = true;
}
Asteroid::Asteroid(Vector2 pos)
{
    // Vector2 center = {-8, -8};
    isActiveAndEnabled = true;
    position = pos;
    topLeftCorner = {position.x - (float)GetScreenWidth()/2, position.y - (float)GetScreenWidth()/2};
    if(!isPregenerated)//only randomize non-pre-generated asteroids
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
        if(cell.Draw() == 1)//cell was disabled because of step
        {
            // UpdateLighting({});
        }
    }
    // for(auto& light : edgeLights)
    // {
    //     DrawRectangle(light.position.x + position.x, light.position.y + position.y, 24, 24, YELLOW);
    // }
    // BeginBlendMode(BLEND_MULTIPLIED);
    //     DrawTextureEx(shading, {topLeftCorner.x + localCenterFirst.x, topLeftCorner.y + localCenterFirst.y}, 0.0f, 4, WHITE);
    // EndBlendMode();
    // for(auto& cell : darkCells100)
    // {
    //     cell.Draw();
    // }
    // DrawRectangleV({topLeftCorner.x + localCenterFirst.x , topLeftCorner.y + localCenterFirst.y}, {(float)GetScreenWidth()*2, (float)GetScreenWidth()*2}, {255, 0, 255, 127});
}
bool Asteroid::IsInsideCircle(Vector2 point, int xcenter, int ycenter, int r)
{
    return (pow(point.x - xcenter, 2) + pow(point.y - ycenter, 2)) < pow(r, 2);
}

vector<Vector2Bool> Asteroid::Generate(int r)
{
    float radius = r;
    float d = 2*radius;
    Vector2 center = {radius, radius};
    vector<Vector2Bool> circle = MidPointCircleDraw(center.x, center.y, radius);
    vector<Vector2Bool> filledCircle = circle;
    for(float y = 0; y < d; y++)
    { 
        for(float x = 0; x < d; x++)
        {
            if(IsInsideCircle({x, y}, center.x, center.y, radius))
            {
                bool isNotCopy = true;
                for(Vector2Bool& vec : circle)
                {
                    if(vec.x == x && vec.y == y)//is a copy
                    {
                        isNotCopy = false;
                        break;
                    }
                }
                if(isNotCopy)
                    filledCircle.push_back({x,y,false});
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
vector<Vector2Bool> Asteroid::MidPointCircleDraw(int xcenter, int ycenter, int radius){//WILL ADD VECTOR2BOOL RETURN
    vector<Vector2Bool> circle;

    int x = 0;
    int y = radius;
    int p = 1 - radius;
    vector<Vector2> c1 = drawcircle(xcenter, ycenter, x, y);
    for (Vector2& vec2 : c1)
    {
        circle.push_back({vec2.x, vec2.y, true});
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
           circle.push_back({vec2.x, vec2.y, true});
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
        vector<Vector2Bool> vecs = Generate(randomRadius);
        // vector<Vector2> outline1 = MidPointCircleDraw(randomRadius, randomRadius, randomRadius);
        // vector<Vector2> dark50; //= Generate(randomRadius);
        // for(auto& vec : vecs)
        // {
        // }
        
        

        for(int j = 0; j < vecs.size(); j++)
        {
            vector<Vector2Bool> outline1 = MidPointCircleDraw(randomRadius, randomRadius, randomRadius);
            Vector2Bool vec = vecs[j];
            Cell cell = Cell();
            cell.position = {GetScreenWidth()/2 + (cell.GetUnitSize().x * (vec.x + localCenter.x) ), GetScreenWidth()/2 + (cell.GetUnitSize().y * (vec.y + localCenter.y))};
            cell.relativeTo = position;
            cell.isOnEdge = vec.boolean;
            if(i == 0)
                localCenterFirst = {cell.GetUnitSize().x * localCenter.x, cell.GetUnitSize().y * localCenter.y};
            cell.id = GetRandomValue(2, 3);//random center
            // cell.id = 9;
            // cell.outlineId = 2;
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
    // std::sort(cells.begin(), cells.end()); // sort the cells vector
    // cells.erase(std::unique(cells.begin(), cells.end()), cells.end()); // remove duped cells

    // for(auto& cell : cells)
    // {
    //     if(cell.isOnEdge)
    //     {
    //         edgeLights.push_back(Light(cell.position, 0, 48));
    //     }
    // }
}

Vector2 Asteroid::WorldToGrid(Vector2 pixelCoords)
{
    return {pixelCoords.x / 12, pixelCoords.y / 12};
}
Vector2 Asteroid::GridToWorld(Vector2 gridCoords)
{
    return {gridCoords.x * 12, gridCoords.y * 12};
}


// void Asteroid::UpdateLighting(std::vector<Light> additionalLights)
// {
//     vector<Light> lights = additionalLights;

//     Image calculatedShading = GenImageColor((GetScreenWidth()*2)/4, (GetScreenWidth()*2)/4, {0, 0, 0, 0});
//     // Color* pixels = (Color*)calculatedShading.data;
//     for(auto& vec_ : cells)
//     {
//         if(vec_.isActiveAndEnabled)
//         {
//         // position.x - (float)GetScreenWidth()/2, position.y - (float)GetScreenWidth()/2
//             Vector2 pixelVec = {vec_.position.x/4, vec_.position.y/4};
//             for(int x = 0; x < 12; x++)
//             {
//                 for(int y = 0; y < 12; y++)
//                 {
//                     double a = 0;//alpha channel for pixel
//                     for(auto& light : edgeLights)
//                     {
//                         a = 1 - Clamp01(a + (light.radiusInPixels / Distance({vec_.position.x + x*4, vec_.position.y + y*4}, light.position) - light.threshold));
//                     }
//                     // int a = 0.5 * 255;
//                     Vector2 newPixelVec = {(int)(pixelVec.x + x + GetScreenWidth()/8), (int)(pixelVec.y + y + GetScreenWidth()/8)};//{(int)(pixelVec.x + GetScreenWidth()/2 + x), (int)(pixelVec.y + GetScreenWidth()/2 + y)};
//                     // std::cout<<"X: "<<newPixelVec.x << "Y: " << newPixelVec.y << std::endl;
//                     ImageDrawPixel(&calculatedShading, newPixelVec.x, newPixelVec.y, {0, 0, 0, (unsigned char)(a*255)});
//                     //DrawRectangleV({newPixelVec.x + asteroid.topLeftCorner.x, newPixelVec.y + asteroid.topLeftCorner.y}, {48, 48}, WHITE);
//                 }
//             }
//         }
//     }
//     shading = LoadTextureFromImage(calculatedShading);
//     UnloadImage(calculatedShading);
// }

float Asteroid::Clamp01(double n)
{
    if(n > 1)
        return 1;
    else if (n < 0)
        return 0;
    else
        return n;
}
double Asteroid::Distance(Vector2 p1, Vector2 p2)
{
    return std::sqrt(std::pow(p2.x-p1.x, 2) + std::pow(p2.y-p1.y, 2));
}