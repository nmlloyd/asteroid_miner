#include "manager.hpp"
#include <iostream>

Manager::Manager()
{
    asteroid.position = {(GetScreenWidth() )/2, (GetScreenHeight() )/2};
    std::cout << asteroid.position.x << ", " << asteroid.position.y << std::endl;
}
void Manager::Start()
{
    asteroid.Draw();
}
void Manager::Update()
{
    asteroid.Update();
}