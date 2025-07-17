#include "mouse.hpp"

Mouse::Mouse()
{
}
Vector2 Mouse::GetCollider()
{
    return {position.x, position.y};
}
void Mouse::Update()
{
    position = GetMousePosition();
}