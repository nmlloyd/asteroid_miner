#include "gameobject.hpp"

GameObject::GameObject()
{
}

GameObject::GameObject(Transform2D _transform, Texture2D _sprite)
{
    transform = _transform;
    sprite = _sprite;
    collider = {transform.position.x, transform.position.y, (float)sprite.width * transform.scale, (float)sprite.height * transform.scale};//set collider, will be accessed by deriving class
}
void GameObject::Draw()
{
    DrawTextureEx(sprite, transform.position, transform.rotation, transform.scale, {255, 255, 255, 255});//WHITE);
}
void GameObject::Update()
{
    transform.position.x += velocity.x / 60;
    transform.position.y += velocity.y / 60;
}