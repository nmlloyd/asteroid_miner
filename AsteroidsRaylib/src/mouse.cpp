#include "mouse.hpp"

Mouse::Mouse()
{
}
Vector2 Mouse::GetCollider()
{
    return {position.x, position.y};
}
// Rectangle Mouse::GetApproxCollider() //gets a 2 tiles x 2 tiles wide rectangle centered at the mouse aligned
void Mouse::Update()
{
    position = GetMousePosition();
}