#include "asteroid.hpp"

Asteroid::Asteroid()
{
    grid = {
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 0}
    };
    for(int y = 0; y < grid.size(); y++)
    {
        for(int x = 0; x < grid[0].size(); x++)
        {
            Cell cell = Cell();
            if(grid[y][x] == 1)//add cell
            {
                cell.position = {(GetScreenWidth() + cell.GetUnitSize().x * (x + 1))/2, (GetScreenHeight() + cell.GetUnitSize().y * (y + 1))/2};
                cells.push_back(cell);
            }
        }
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
        cell.Draw();
    }
}