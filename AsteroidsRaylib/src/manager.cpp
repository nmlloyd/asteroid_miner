#include "manager.hpp"
#include <iostream>
#include <cmath>
#include <fstream> 
using namespace std;
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

vector<Cell> Manager::LoadStructureFromFile(std::string fileName)
{
    int w = 0;
    int h = 0;
    Vector2 pos = {48, 48};
    int outline = 1;
    int y = 0;//line counter
    vector<Cell> cells {};

    std::string line;
    std::ifstream fptr("Assets/" + fileName);
    std::getline(fptr, line);
    while (std::getline(fptr, line)) //iterate through each line
    {
        if(line[0] == 'm')//dimensions
        {
            w = line[1] - '0';
            h = line[2] - '0';
            // std::cout << "Width: " << w << "  Height: " << h << std::endl;
        }
        else if(line[0] == 'o')//outline ID
        {
            outline = line[1] - '0';
            // std::cout << "Outline ID: " << outline << std::endl;
        }
        else if(line[0] == 'x')//position x
        {
            pos.x *= (line[1] - '0');
            // std::cout << "Outline ID: " << outline << std::endl;
        }
        else if(line[0] == 'y')//position y
        {
            pos.y *= (line[1] - '0');
            // std::cout << "Outline ID: " << outline << std::endl;
        }
        else //regular line
        {
            for(int i = 0; i < line.size(); i++)
            {
                Cell cell = Cell();
                cell.outlineId = outline;//set outline
                if(line[i] != ' ' && line[i] > 47)//is an ID
                {
                    // cout<<"Index: "<< i<<endl;
                    // if(line[i] - '0' + 1 == 15)//is cell
                    // {
                    //     cout<<":("<<endl;
                    // }
                    cell.id = line[i] - '0' + 1;//set cell ID
                    cell.position = {(float)(i) * 48 + pos.x, (float)y * 48 + pos.y};//set position based on the lines of the file and the position of the characters
                    cell.allowBreaking = false;
                    cells.push_back(cell);
                }
                // else //empty space
                // {

                // }
            }
            y++;
            // std::cout << line << std::endl;
        }
    }
    return cells;
}

void Manager::Start()
{

    font = LoadFont("Font/monogram.ttf");
    player = Player();
    player.transform = {{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0.0f, 1.0f};
    player.transform.position = {0, 0};
    player.sprite = LoadTexture("Graphics/player_putin_2x4.png");
    // asteroid.position = {(float)(GetScreenWidth() )/2, (float)(GetScreenHeight() )/2};
    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;
    camera = {0};//create new camera
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };//set camera's position to the player
    camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };//center camera on player
    camera.rotation = 0.0f;//make sure the camera doesnt rotate
    camera.zoom = 1.0f;//set starting zoom

    SetRandomMission();//create new random mission

    // computerUI.isActiveAndEnabled = true;//set computer ui to on for debug
    computerUI.randomizedMission = mission;


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
    if(scene == Scenes::Base)//load meteorite and spaceship 
    {
        LoadSceneBase();
    }
    else
    {
        player.bounce = 0.2;
    }


    objective = Objective::GoToComputer;
    
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
            if(showDebug)
            {
                for(auto& cell : ast.cells)
                {
                    // cout << cell.isActiveAndEnabled << endl;
                    DrawRectangleRec(cell.GetCollider(), WHITE);//draw debug colliders
                }
            }
        }
        if(showDebug)
        {
            DrawRectangleRec(player.GetCollider(), PURPLE);
            Vector2 worldPosButton = GetScreenToWorld2D({computerUI.GetButtonCollider().x, computerUI.GetButtonCollider().y}, camera);
            DrawRectangleRec({worldPosButton.x, worldPosButton.y, computerUI.GetButtonCollider().width, computerUI.GetButtonCollider().height}, RED);
                    
        }
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
    switch (objective)//draw objective in top left
    {
        case Objective::BeamDown:
            DrawTextEx(font, "Current Objective:\nBeam down to the Asteroid Belt", {10, 10}, 30, 3, WHITE);
            break;
        case Objective::CompleteMission:
            switch(mission.oreToMine)
            {
                case OreTile::Putin:
                    string str = "Current Objective:\nFind and Collect " + to_string(mission.quantity) + " Putonium";
                    DrawTextEx(font, str.c_str(), {10, 10}, 30, 3, WHITE);
                    break;
            }
            break;
        case Objective::GoToComputer:
            DrawTextEx(font, "Current Objective:\nGo to the Computer to start the next mission", {10, 10}, 30, 3, WHITE);
            break;
    }

    computerUI.Draw();//draw computer ui if enabled
    DrawRectangle(mouse.position.x, mouse.position.y, 10, 10, RED);//Draw mouse cursor
    // Cell cell = Cell();
    // cell.position = {1280, 800};
    // cell.Draw();
}
void Manager::Update()
{
    bool isFreeCam = false;
    bool reflectedThisFrame = false;

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

    if(IsKeyPressed(KEY_F1))
    {
        showDebug = !showDebug;//toggle debug
    }
    if(IsKeyPressed(KEY_F2))//debug switch scenes
    {
        if(scene == Scenes::Base)
            ChangeScene(Scenes::Field);//asteroid field
        else if(scene == Scenes::Field)//spaceship
        {
            ChangeScene(Scenes::Base);
            // field.clear();
        }
            //ChangeScene(1);//starship
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

    if(continueLoop) 
    {
        for(auto& ast : field)
        {
            if(ast.isActiveAndEnabled && continueLoop)
            {
                for(auto& cell : ast.cells)
                {
                    // std::cout<<"Manager::Update() cell.id: "<<cell.id<<endl;
                    if(IsMouseButtonPressed(0))
                    {
                        // std::cout << "collided with cell at position (" << cell.position.x << ", " << cell.position.y << ")" << std::endl;
                        // std::cout << "mouse: " << mouse.GetCollider().x << ", " << mouse.GetCollider().y << std::endl;
                        // std::cout << cell.GetCollider().x << ", " << cell.GetCollider().y << ", " << cell.GetCollider().width << ", " << cell.GetCollider().height << std::endl;
                        if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), (cell.GetCollider())))
                        {
                            if(cell.allowBreaking)
                            {
                                // std::cout<<"Rectangle:"<<"X: "<<cell.GetCollider().x<<"Y: "<<cell.GetCollider().y<<"W: "<<cell.GetCollider().width<<"H: "<<cell.GetCollider().height<<std::endl;
                                float mineSpeed = 1.0f;
                                cell.step += mineSpeed;
                                // break;
                            }
                            else if(cell.id == 14)//check if is computer
                            {
                                cout << "Toggled computer screen" << endl;
                                ToggleComputerScreen();
                            }
                            else if(cell.id == 16)//check if is teleporter button
                            {
                                // field.clear();
                                if(objective == Objective::BeamDown)
                                {
                                    objective = Objective::CompleteMission;
                                    ChangeScene(Scenes::Field);//change scene to asteroids
                                    continueLoop = false;
                                    break;
                                }
                            }
                        }
                        
                    }
                    if (cell.allowCollisions && cell.isActiveAndEnabled && !reflectedThisFrame)
                    {
                        // Predict player's next position (next frame collider)
                        Rectangle nextPlayerCollider = {
                            player.GetCollider().x + player.velocity.x / 60.0f,
                            player.GetCollider().y + player.velocity.y / 60.0f,
                            player.GetCollider().width,
                            player.GetCollider().height
                        };

                        Rectangle tileCollider = cell.GetCollider();

                        if (CheckCollisionRecs(nextPlayerCollider, tileCollider))
                        {
                            // Store previous collider before applying velocity
                            Rectangle prevPlayerCollider = player.GetCollider();

                            // Compute centers
                            float prevCenterX = prevPlayerCollider.x + prevPlayerCollider.width / 2.0f;
                            float prevCenterY = prevPlayerCollider.y + prevPlayerCollider.height / 2.0f;
                            float tileCenterX = tileCollider.x + tileCollider.width / 2.0f;
                            float tileCenterY = tileCollider.y + tileCollider.height / 2.0f;

                            // Deltas
                            float dx = prevCenterX - tileCenterX;
                            float dy = prevCenterY - tileCenterY;

                            float combinedHalfWidths = (prevPlayerCollider.width + tileCollider.width) / 2.0f;
                            float combinedHalfHeights = (prevPlayerCollider.height + tileCollider.height) / 2.0f;

                            float crossWidth = combinedHalfWidths * dy;
                            float crossHeight = combinedHalfHeights * dx;

                            // Undo movement to avoid pushing inside
                            player.transform.position.x -= player.velocity.x / 60.0f;
                            player.transform.position.y -= player.velocity.y / 60.0f;

                            // Determine collision side
                            if (crossWidth > crossHeight)
                            {
                                if (crossWidth > -crossHeight)
                                {
                                    // std::cout << "Collision: TOP\n";
                                    player.velocity.y = abs(player.bounce * player.velocity.y);
                                    reflectedThisFrame = true;
                                }
                                else
                                {
                                    // std::cout << "Collision: RIGHT\n";
                                    player.velocity.x = -abs(player.bounce * player.velocity.x);
                                    reflectedThisFrame = true;
                                }
                            }
                            else
                            {
                                if (crossWidth > -crossHeight)
                                {
                                    // std::cout << "Collision: LEFT\n";
                                    player.velocity.x = abs(player.bounce * player.velocity.x);
                                    reflectedThisFrame = true;
                                }
                                else
                                {
                                    // std::cout << "Collision: BOTTOM\n";
                                    player.velocity.y = -abs(player.bounce * player.velocity.y);
                                    reflectedThisFrame = true;
                                }
                            }
                        }
                    }
                }
                ast.Update();
            }
        }
    }
    continueLoop = true;

    Vector2 worldPosButton = GetScreenToWorld2D({computerUI.GetButtonCollider().x, computerUI.GetButtonCollider().y}, camera);
    if(computerUI.isActiveAndEnabled)//clicked button
    {
        if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), {worldPosButton.x, worldPosButton.y, computerUI.GetButtonCollider().width, computerUI.GetButtonCollider().height}))
        {
            if(IsMouseButtonDown(0))
            {
                computerUI.SetButtonDown();
                objective = Objective::BeamDown;
            }
        }
        if(IsKeyPressed(KEY_ENTER))
        {
            ToggleComputerScreen();
        }
    }
    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;

    player.Update();

    Vector2 playerScreenPos = {floorf(player.transform.position.x / GetScreenWidth()), floorf(player.transform.position.y / GetScreenWidth())};


    if(scene == Scenes::Field)
    {
        LoadSceneField(playerScreenPos, false);
    }
    // else if (scene == 1)
    // {
    //     LoadStructureFromFile("test.grid");
    // }




    // asteroid.Update();
    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));
    camera.target = { player.transform.position.x + halfW, player.transform.position.y + halfH };

    // DestroyInactiveStars();
    // if(IsKeyPressed(KEY_L))
    // {
    //     field[0].UpdateLighting({});//test one asteroid only
    // }

    // lastPlayerScreenPos = playerScreenPos;

    // for(auto& ast : field){
    //     cout <<"X: "<< ast.gridPosition.x <<"Y: " <<ast.gridPosition.y << endl;
    //     cout <<"Cell size: " << ast.cells.size()<<endl;
    //     cout <<"Texture ID: "<< ast.cells[10].unitTex->id<<endl;
    // }
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
void Manager::ChangeScene(Scenes sceneId)
{
    if(sceneId == Scenes::Field)//asteroids
    {
        // ;//clear vector
        player.transform.position = {0, 0};//reset pos
        player.bounce = 0.2;
        scene = Scenes::Field;
        LoadSceneField({0, 0}, true);
    }
    else if(sceneId == Scenes::Base)//spaceship
    {
        player.transform.position = {0, 0};
        LoadSceneBase();
        scene = Scenes::Base;
    }
    scene = sceneId;//set scene
}

void Manager::LoadSceneBase()
{
    field.clear();

    
    SetRandomMission();//create new random mission
    computerUI.randomizedMission = mission;//set ui mission for use later
    computerUI.isButtonDown = false;//reset computer button


    player.bounce = 0;//make it so the player doesnt bounce in the spaceship
    //declare structures
    Asteroid meteorite = Asteroid();//meteorite
    Asteroid spaceship = Asteroid();//spaceship
    Asteroid background = Asteroid();//background tiles of spaceship
    // Asteroid tele = Asteroid();//teleporter collision

    //set positions
    meteorite.position = {0,0};
    spaceship.position = {0,0};
    background.position = {0,0};
    // tele.position = {0,0};

    meteorite.gridPosition = {0,0};
    spaceship.gridPosition = {0,1};
    background.gridPosition = {1,0};
    // tele.gridPosition = {1,1};

    //set topLeftCorner in case of shading
    meteorite.topLeftCorner = {-(float)GetScreenWidth()/2, -(float)GetScreenWidth()/2};
    spaceship.topLeftCorner = {-(float)GetScreenWidth()/2, -(float)GetScreenWidth()/2};
    background.topLeftCorner = {-(float)GetScreenWidth()/2, -(float)GetScreenWidth()/2};
    // tele.topLeftCorner = {-(float)GetScreenWidth()/2, -(float)GetScreenWidth()/2};

    //define structures
    meteorite.cells = LoadStructureFromFile("meteorite.grid");
    spaceship.cells = LoadStructureFromFile("spaceship.grid");
    background.cells = LoadStructureFromFile("spaceship.bkg");
    // tele.cells = LoadStructureFromFile("teleporter_floor.grid");

    //make background not collide with anything and make all structures unbreakable
    for(auto& cell : background.cells)
    {
        cell.allowBreaking = false;
        cell.allowCollisions = false;
        cell.drawOutline = true;
        cell.color = WHITE;

        // if(cell.id == 14)//if it is a computer then allow collision
        // {
        //     cell.allowCollisions = true;
        // }
    }
    for(auto& cell : spaceship.cells)
    {
        cell.allowBreaking = false;
        cell.color = WHITE;
    }
    // for(auto& cell : tele.cells)//make an invisible collider ofr the teleporter
    // {
    //     cell.allowBreaking = false;
    //     cell.drawOutline = false;
    //     cell.color = WHITE;
    // }
    for(auto& cell : meteorite.cells)
    {
        cell.allowBreaking = false;
    }
    //push all structures for drawing
    field.push_back(background);
    field.push_back(spaceship);
    field.push_back(meteorite);
}
void Manager::LoadSceneField(Vector2 playerScreenPos, bool erase)
{
    cout<<"LoadSceneField ran"<<endl;
    if(erase)
        field.erase(field.begin(), field.end());
    //generate grid of 9 asteroids around the player
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
}

void Manager::SetRandomMission()
{
    MiningMission randomMission;
    int amountToMine = GetRandomValue(1, 10) * 10;
    int randomOre = GetRandomValue(0, 2);
    switch(randomOre)
    {
        case 0://putin random
            randomMission.oreToMine = OreTile::Putin;
            cout<<"Putin x" + to_string(amountToMine)<<endl;
            break;
        case 1://will add viridite later
            randomMission.oreToMine = OreTile::Putin;
            cout<<"Putin x" + to_string(amountToMine)<<endl;
            break;
        case 2://will add the blue ore later
            randomMission.oreToMine = OreTile::Putin;
            cout<<"Putin x" + to_string(amountToMine)<<endl;
            break;
    }
    randomMission.quantity = amountToMine;
    mission = randomMission;
}


void Manager::ToggleComputerScreen()
{
    computerUI.isActiveAndEnabled = !computerUI.isActiveAndEnabled;//toggle
}
