#include "manager.hpp"
#include <iostream>
#include <cmath>

Manager::Manager()
{
    
}

// void Manager::UpdateLighting(std::vector<Light> additionalLights, Asteroid& asteroid)
// {
//     Image calculatedShading = GenImageColor(GetScreenWidth()*2, GetScreenWidth()*2, {0, 255, 0, 127});
//     // Color* pixels = (Color*)calculatedShading.data;
//     for(auto& vec_ : asteroid.cells)
//     {
//         if(vec_.isActiveAndEnabled)
//         {
//         // position.x - (float)GetScreenWidth()/2, position.y - (float)GetScreenWidth()/2
//             Vector2 pixelVec = {vec_.position.x, vec_.position.y};
//             for(int x = 0; x < 48; x++)
//             {
//                 for(int y = 0; y < 48; y++)
//                 {
//                     int a = 0.5 * 255;//alpha channel
//                     Vector2 newPixelVec = {(int)(pixelVec.x + x + GetScreenWidth()/2), (int)(pixelVec.y + y + GetScreenWidth()/2)};//{(int)(pixelVec.x + GetScreenWidth()/2 + x), (int)(pixelVec.y + GetScreenWidth()/2 + y)};
//                     // std::cout<<"X: "<<newPixelVec.x << "Y: " << newPixelVec.y << std::endl;
//                     ImageDrawPixel(&calculatedShading, newPixelVec.x, newPixelVec.y, {255, 0, 0, (unsigned char)a});
//                     //DrawRectangleV({newPixelVec.x + asteroid.topLeftCorner.x, newPixelVec.y + asteroid.topLeftCorner.y}, {48, 48}, WHITE);
//                 }
//             }
//         }
//     }
//     asteroid.shading = LoadTextureFromImage(calculatedShading);
//     UnloadImage(calculatedShading);
// }

void Manager::GenerateAsteroidsGrid(Vector2 positionInScreenWidths)
{
    int rnd = GetScreenWidth()/2;
    // float gridX = GetScreenWidth();//480.0f;
    // float gridY = GetScreenHeight();
    int rx = GetRandomValue(-rnd, rnd);
    int ry = GetRandomValue(-rnd, rnd);
    Vector2 scvec = {(positionInScreenWidths.x * GetScreenWidth()*2), (positionInScreenWidths.y * GetScreenWidth()*2)};
    Vector2 vec = {rx + (positionInScreenWidths.x * GetScreenWidth()*2), ry + (positionInScreenWidths.y * GetScreenWidth()*2)};

    bool foundCopy = false;
    for(auto& fieldNode : field)
    {
        if(fieldNode.gridPosition.x == scvec.x && fieldNode.gridPosition.y == scvec.y)//found copy
        {
            foundCopy = true;
            break;
        }

    }
    if(!foundCopy)
    {
        Asteroid ast = Asteroid(vec);
        ast.gridPosition = scvec;
        if(ast.isActiveAndEnabled)
            // ast.UpdateLighting({});
        field.push_back(ast);
    }
}


void Manager::Start()
{
    player = Player();
    player.transform = {{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0.0f, 1.0f};
    player.transform.position = {0, 0};
    player.sprite = LoadTexture("Graphics/small_putin_square.png");
    // asteroid.position = {(float)(GetScreenWidth() )/2, (float)(GetScreenHeight() )/2};
    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;
    camera = {0};
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };
    camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int rnd = 60;
    float gridX = 123.0f;
    float gridY = 123.0f;
    for (int y = 0; y < ceilf(GetScreenHeight()/gridY); y++)
    {
        for (int x = 0; x < ceilf(GetScreenWidth()/gridX); x++)
        {
            int rx = GetRandomValue(-rnd, rnd);
            int ry = GetRandomValue(-rnd, rnd);
            Vector2 vec = {x*gridX + rx, y*gridY + ry};
            Star star;
            star.position = vec;
            star.isActive = true;
            star.player = player;
            stars.push_back(star);
        }
    }
    
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
    for(int i = 0; i < stars.size(); i++)
    {
        stars[i].Draw();
    } 
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
    
        for(auto& ast : field)
        {
            if(sqrt(pow(ast.position.x - player.transform.position.x, 2) + pow(ast.position.y - player.transform.position.y, 2)) >= GetScreenWidth()*4)
                ast.isActiveAndEnabled = false;
            else
                ast.isActiveAndEnabled = true;
            if(ast.isActiveAndEnabled)
            {
                ast.Draw();
                // DrawRectangle(ast.position.x - (float)GetScreenWidth()/2, ast.position.y - (float)GetScreenWidth()/2, (float)GetScreenWidth()*2, (float)GetScreenWidth()*2, {0, 0, 255, 127});
                // for(auto& pixel : ast.shading)
                // {
                //     DrawPixelV(pixel.position, {255, 0, 0, (unsigned char)roundf(pixel.alpha * 255)});
                //     // std::cout << pixel.position.x << pixel.position.y << std::endl;
                // }
            }
            for(auto& cell : ast.cells)
            
            {
                // DrawRectangleRec(cell.GetCollider(), WHITE);
            }
        }
        DrawRectangleRec(player.GetCollider(), PURPLE);
        // asteroid.Draw();
        player.Draw();

        
        // if(IsKeyPressed(KEY_B))
        // {
        //     for(auto& asteroid : field)
        //     {
        //         if(asteroid.isActiveAndEnabled)
        //             asteroid.UpdateLighting({});
        //     }
        //         // for(auto& cell : field[0].cells)
        //         // {
        //         //     std::cout << "Cell position: " << cell.position.x << ", " << cell.position.y << std::endl;
        //         // }
        // }
        // // BeginBlendMode(BLEND_MULTIPLIED);
        //     // DrawTexture(shading, );
        // EndBlendMode();
    EndMode2D();
    
    DrawRectangle(mouse.position.x, mouse.position.y, 10, 10, RED);
    // Cell cell = Cell();
    // cell.position = {1280, 800};
    // cell.Draw();
}
void Manager::Update()
{
    bool isFreeCam = false;

    mouse.Update();

    if(isFreeCam)
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
    }
    else
    {
        
        if(IsKeyDown(KEY_A))
        {
            player.velocity.x -= player.speed/3;
        }
        else if(IsKeyDown(KEY_D))
        {
            player.velocity.x += player.speed/3;
        }
        if(IsKeyDown(KEY_W))
        {
            player.velocity.y -= player.speed/3;
        }
        else if(IsKeyDown(KEY_S))
        {
            player.velocity.y += player.speed/3;
        }
        
        // if(abs(player.velocity.x) > player.speed)
        // {
        //     player.velocity.x = player.speed;
        // }
        // if(abs(player.velocity.y) > player.speed)
        // {
        //     player.velocity.y = player.speed;
        // }
    }
    // double magnitude = sqrt(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
    // player.velocity.x /= magnitude;
    // player.velocity.y /= magnitude;
    if(isFreeCam)
    {
        player.velocity.x *= 600 * player.speed;
        player.velocity.y *= 600 * player.speed;
    }
    else
    {
        player.velocity.y = Clamp(-player.speed * 60, player.speed * 60, player.velocity.y);
        player.velocity.x = Clamp(-player.speed * 60, player.speed * 60, player.velocity.x);
    }
    // else
    // {
    //     player.velocity.x *= 60;
    //     player.velocity.y *= 60;
    // }
    // for(auto& cell : asteroid.cells)
    // {
    //     if(CheckCollisionRecs(cell.GetCollider(), {player.GetCollider().x + player.velocity.x, player.GetCollider().y + player.velocity.y, player.GetCollider().width, player.GetCollider().height}))
    //     {//will collide next frame
    //         player.velocity = {0, 0};
    //     }
    // }


    for(auto& ast : field)
    {
        if(ast.isActiveAndEnabled)
        {
            for(auto& cell : ast.cells)
            {
                
                if(IsMouseButtonPressed(0))
                {
                    // std::cout << "collided with cell at position (" << cell.position.x << ", " << cell.position.y << ")" << std::endl;
                    // std::cout << "mouse: " << mouse.GetCollider().x << ", " << mouse.GetCollider().y << std::endl;
                    // std::cout << cell.GetCollider().x << ", " << cell.GetCollider().y << ", " << cell.GetCollider().width << ", " << cell.GetCollider().height << std::endl;
                    if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), (cell.GetCollider())))
                    {
                        std::cout<<"Rectangle:"<<"X: "<<cell.GetCollider().x<<"Y: "<<cell.GetCollider().y<<"W: "<<cell.GetCollider().width<<"H: "<<cell.GetCollider().height<<std::endl;
                        float mineSpeed = 2.0f;
                        cell.step += mineSpeed;
                        // break;
                    }
                }
                if(cell.isActiveAndEnabled)
                {
                    //player collision detection
                    if(CheckCollisionRecs({player.GetCollider().x + player.velocity.x / 60, player.GetCollider().y + player.velocity.y / 60, player.GetCollider().width, player.GetCollider().height}, cell.GetCollider()))//player collides with a tile next frame
                    {
                        Vector2 deltaVector = {player.GetCollider().x + player.velocity.x / 60 - cell.position.x, player.GetCollider().y + player.velocity.y / 60 - cell.position.y};// delta vector between player and tile
                        // CheckCollisionRec
                        // std::cout << "Collided with player" << std::endl;
                        player.transform.position.x -= player.velocity.x / 60;
                        player.transform.position.y -= player.velocity.y / 60;

                        // if(abs(deltaVector.x) > abs(deltaVector.y))//collided with right/left side of player and left/right side of tile
                        // {
                        //     std::cout << "Reflect x" << std::endl;
                        //     player.velocity.x *= -player.bounce;// reflect x velocity
                        // }
                        // else if(abs(deltaVector.y) > abs(deltaVector.x))//collided with top/bottom side of player and top/bottom side of tile
                        // {
                        //     std::cout << "Reflect y" << std::endl;
                        //     player.velocity.y *= -player.bounce;//reflect y velocity
                        // }
                        player.velocity.x *= -player.bounce;
                        player.velocity.y *= -player.bounce;
                    }
                }
            }
            ast.Update();
        }
    }

    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;

    player.Update();

    Vector2 playerScreenPos = {floorf(player.transform.position.x / GetScreenWidth()), floorf(player.transform.position.y / GetScreenWidth())};


    GenerateAsteroidsGrid({playerScreenPos.x, playerScreenPos.y});
    GenerateAsteroidsGrid({-1+playerScreenPos.x, playerScreenPos.y});
    GenerateAsteroidsGrid({playerScreenPos.x, -1+playerScreenPos.y});
    GenerateAsteroidsGrid({-1+playerScreenPos.x, -1+playerScreenPos.y});
    GenerateAsteroidsGrid({1+playerScreenPos.x, -1+playerScreenPos.y});
    GenerateAsteroidsGrid({1+playerScreenPos.x, playerScreenPos.y});
    GenerateAsteroidsGrid({1+playerScreenPos.x, 1+playerScreenPos.y});
    GenerateAsteroidsGrid({-1+playerScreenPos.x, 1+playerScreenPos.y});
    GenerateAsteroidsGrid({-1+playerScreenPos.x, playerScreenPos.y});
    GenerateAsteroidsGrid({playerScreenPos.x, 1+playerScreenPos.y});




    // asteroid.Update();
    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };

    // DestroyInactiveStars();
    // if(IsKeyPressed(KEY_L))
    // {
    //     field[0].UpdateLighting({});//test one asteroid only
    // }

    // lastPlayerScreenPos = playerScreenPos;
}

float Manager::Clamp01(float n)
{
    if(n > 1)
        return 1;
    else if (n < 0)
        return 0;
    else
        return n;
}
float Manager::Clamp(float min, float max, float n)
{
    if(n > max)
        return max;
    else if (n < min)
        return min;
    else
        return n;
}
double Manager::Distance(Vector2 p1, Vector2 p2)
{
    return std::sqrt(std::pow(p2.x-p1.x, 2) + std::pow(p2.y-p1.y, 2));
}