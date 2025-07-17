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
    asteroid.position = {(float)(GetScreenWidth() )/2, (float)(GetScreenHeight() )/2};
    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;
    camera = {0};
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };
    camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
}
void Manager::DestroyInactiveStars()
{
    // for(auto i = stars.begin(); i != stars.end();)
    // {
    //     if(!i->isActive)
    //         i = stars.erase(i);
    //     else
    //         i++;
    // }
}

void Manager::Draw()
{
    BeginMode2D(camera);
        // int rnd = 60;
        // float gridX = 123.0f;
        // float gridY = 123.0f;
        // for (int y = 0; y < ceilf(GetScreenHeight()/gridY); y++)
        // {
        //     for (int x = 0; x < ceilf(GetScreenWidth()/gridX); x++)
        //     {
        //         int rx = GetRandomValue(-rnd, rnd);
        //         int ry = GetRandomValue(-rnd, rnd);
        //         Vector2 vec = {x*gridX + rx, y*gridY + ry};
        //         stars.push_back(vec);
        //     }
        // }
        // for(int i = 0; i < stars.size(); i++)
        // {
        //     DrawRectangle(stars[i].x, stars[i].y, 2, 2, WHITE);
        // } 
    
        asteroid.Draw();
        player.Draw();
    EndMode2D();
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
    // for(auto& cell : asteroid.cells)
    // {
    //     if(CheckCollisionRecs(cell.GetCollider(), {player.GetCollider().x + player.velocity.x, player.GetCollider().y + player.velocity.y, player.GetCollider().width, player.GetCollider().height}))
    //     {//will collide next frame
    //         player.velocity = {0, 0};
    //     }
    // }

    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;

    player.Update();
    asteroid.Update();
    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };

    DestroyInactiveStars();
}