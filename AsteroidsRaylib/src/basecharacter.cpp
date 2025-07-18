#include "basecharacter.hpp"

BaseCharacter::BaseCharacter()
{

}
BaseCharacter::BaseCharacter(Transform2D _transform, Texture2D _sprite)
{
    transform = _transform;
    sprite = _sprite;
}
void BaseCharacter::Draw()
{
    DrawTextureEx(sprite, transform.position, transform.rotation, transform.scale, {255, 255, 255, 255});//WHITE);
}
void BaseCharacter::Update()
{
    transform.position.x += velocity.x / 60;
    transform.position.y += velocity.y / 60;
}
Rectangle BaseCharacter::GetCollider()
{
    return {transform.position.x, transform.position.y, (float) sprite.width, (float) sprite.height};
}