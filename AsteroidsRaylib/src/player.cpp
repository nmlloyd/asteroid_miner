#include "player.hpp"

Player::Player()
{
}

Player::Player(Transform2D _transform, Texture2D _sprite)
{
    transform = _transform;
    sprite = _sprite;
}
