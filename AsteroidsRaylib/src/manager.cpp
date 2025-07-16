#include "manager.hpp"
#include <iostream>
#include <cmath>

Manager::Manager()
{
    
}
void Manager::Start()
{
    player = Player();
    player.transform = {{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0.0f, 4.0f};
    player.transform.position = {0, 0};
    player.sprite = LoadTexture("Graphics/test_player.png");
    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;
    camera = {0};
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };
    camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    asteroid.position = {(float)(GetScreenWidth() )/2, (float)(GetScreenHeight() )/2};
}
void Manager::Draw()
{
    asteroid.Draw();
    player.Draw();
    // Cell cell = Cell();
    // cell.position = {1280, 800};
    // cell.Draw();
}
void Manager::Update()
{
    if(IsKeyDown(KEY_A))
    {
        player.velocity.x = -1;
    }
    else if(IsKeyDown(KEY_D))
    {
        player.velocity.x = 1;
    }
    else
    {
        player.velocity.x = 0;
    }
    if(IsKeyDown(KEY_W))
    {
        player.velocity.y = -1;
    }
    else if(IsKeyDown(KEY_S))
    {
        player.velocity.y = 1;
    }
    else
    {
        player.velocity.y = 0;
    }
    // double magnitude = sqrt(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
    // player.velocity.x /= magnitude;
    // player.velocity.y /= magnitude;
    player.velocity.x *= 60 * player.speed;
    player.velocity.y *= 60 * player.speed;
    for(auto& cell : asteroid.cells)
    {
        if(CheckCollisionRecs(cell.GetCollider(), {player.GetCollider().x + player.velocity.x, player.GetCollider().y + player.velocity.y, player.GetCollider().width, player.GetCollider().height}))
        {//will collide next frame
            player.velocity = {0, 0};
        }
    }
    player.Update();
    asteroid.Update();
}