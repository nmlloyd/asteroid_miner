#include "asteroid.hpp"
#include <iostream>
#include <cmath>
using namespace std;
Asteroid::Asteroid()
{
    Vector2 center = {-8, -8};
    vector<Vector2> vecs = Generate(8);
    for(int i = 0; i < vecs.size(); i++)
    {
        Vector2 vec = vecs[i];
        Cell cell = Cell();
        cell.position = {GetScreenWidth()/2 + (cell.GetUnitSize().x * (vec.x + center.x)), GetScreenHeight()/2 + (cell.GetUnitSize().y * (vec.y + center.y))};
        cell.id = GetRandomValue(2, 4);//random center
        cells.push_back(cell);
    }
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
 