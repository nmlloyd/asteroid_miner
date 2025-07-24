#include "manager.hpp"
#include <iostream>
#include <cmath>
#include <fstream> 
#include <raymath.h>
using namespace std;
Manager::Manager()
{
    
}
void Manager::Start()
{

    // jumpscare = true;

    widePutinWalkingAnim.animation = LoadImageAnim("Graphics/wide_putin_walking.gif", &widePutinWalkingAnim.frames);
    widePutinWalkingAnim.texture = LoadTextureFromImage(widePutinWalkingAnim.animation);

    font = LoadFont("Font/monogram.ttf");
    noise = LoadTexture("Graphics/red_noise.png");
    player = Player();
    player.transform = {{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0.0f, 1.0f};
    player.transform.position = {0, 0};
    player.sprite = LoadTexture("Graphics/player_putin_2x3.png");
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


    // objective = Objective::Jumpscare;
    // jumpscare = true;

    objective = Objective::GoToComputer;
    pickaxes = 
    {
        {"Stone Pickaxe", 1},
        {"Wolfram Pickaxe", 2},
        {"Graphene Pickaxe", 5},
        {"Wilbur Pickaxe", 10}
    };
    music = LoadMusicStream("Audio/sirenhead.mp3");//sirenhead sound effects
    PlayMusicStream(music);
    music.looping = true;

    staticMusic = LoadMusicStream("Audio/static.mp3");//static effects
    PlayMusicStream(staticMusic);
    staticMusic.looping = true;
    
}
void Manager::Draw()
{
    DrawStarsBackground();


    BeginMode2D(camera);
        DrawAsteroidField();
        DrawDebugColls();
        player.Draw();
        if(showDebug)
            DrawRectangleRec({debugPosition.x * GetScreenWidth(), debugPosition.y * GetScreenWidth(), 120, 120}, PURPLE);
    EndMode2D();


    SwitchObjectiveAndDraw();
    SwitchPickaxeAndDraw();

    // if(jumpscare)
    // {
    //     DrawRectangle(0, 0, 1000, 1000, GREEN);
    // }

    computerUI.Draw();//draw computer ui if enabled
    // Vector2 mouseNormalized = Vector2Scale(Vector2Normalize(mouse.position), maxMineDist * 48);//normalixed mouse pos
    DrawMouseCursor();


    DrawTexture(widePutinWalkingAnim.texture, GetScreenWidth() - widePutinWalkingAnim.texture.width, 0, WHITE);

    DrawTeleportAnimationFromTime();
    if(jumpscare)
    {
        objective = Objective::Jumpscare;
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

        DrawTextureEx(noise, {(float)-GetScreenWidth() + GetRandomValue(-160, 160), (float)-GetScreenHeight() + GetRandomValue(-160, 160)}, 0, 2, {255, 255, 255, 16});//static texture for scare
        SwitchObjectiveAndDraw();
    }
    // Cell cell = Cell();
    // cell.position = {1280, 800};
    // cell.Draw();
}
void Manager::Update()
{
    bool isFreeCam = false;
    bool reflectedThisFrame = false;
    mineSpeed = pickaxes[static_cast<int>(player.pickaxe)].miningSpeed;

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
        if(player.velocity.x != 0 || player.velocity.y != 0)//moving in at least one direction
        {

        }
    }
    else
    {
        
        if(IsKeyDown(KEY_A))
        {
            player.velocity.x -= player.speed/3;
            movedThisFrame = true;
        }
        else if(IsKeyDown(KEY_D))
        {
            player.velocity.x += player.speed/3;
            movedThisFrame = true;
        }
        if(IsKeyDown(KEY_W))
        {
            player.velocity.y -= player.speed/3;
            movedThisFrame = true;
        }
        else if(IsKeyDown(KEY_S))
        {
            player.velocity.y += player.speed/3;
            movedThisFrame = true;
        }
        if(movedThisFrame)
        {
            frameCounter++;
            if (frameCounter >= frameDelay)
            {
                // Move to next frame
                // NOTE: If final frame is reached we return to first frame
                currentAnimFrame++;
                if (currentAnimFrame >= widePutinWalkingAnim.frames) currentAnimFrame = 0;

                // Get memory offset position for next frame data in image.data
                nextFrameDataOffset = widePutinWalkingAnim.animation.width * widePutinWalkingAnim.animation.height * 4 * currentAnimFrame;

                // Update GPU texture data with next frame image data
                // WARNING: Data size (frame size) and pixel format must match already created texture
                UpdateTexture(widePutinWalkingAnim.texture, ((unsigned char *)widePutinWalkingAnim.animation.data) + nextFrameDataOffset);

                frameCounter = 0;
            }
        }
        movedThisFrame = false;
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
    if(IsKeyPressed(KEY_F2) && (objective == Objective::ReturnToBase || objective == Objective::Jumpscare))//debug switch scenes
    {
        jumpscare = false;
        // if(scene == Scenes::Base)
        //     ChangeScene(Scenes::Field);//asteroid field
        if(scene == Scenes::Field)//spaceship
        {
            objective = Objective::GoToComputer;
            showTeleportAnim = true;
            startAnimTime = GetTime() * 60;
            ChangeScene(Scenes::Base);//return to the motherland
            // field.clear();
        }
            //ChangeScene(1);//starship
    }
    if(IsKeyPressed(KEY_KP_1))//debug switch to default pick
    {
        player.pickaxe = PickaxeType::Default;
    }
    else if(IsKeyPressed(KEY_KP_2))//debug switch to medium q pick
    {
        player.pickaxe = PickaxeType::Epic;
    }
    else if(IsKeyPressed(KEY_KP_3))//debug switch to LEGENDARY pick
    {
        player.pickaxe = PickaxeType::Legendary;
    }
    else if(IsKeyPressed(KEY_KP_4))//debug switch to wilbur pick
    {
        player.pickaxe = PickaxeType::Wilbur;
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
        if(!showDebug)
        {
            player.velocity.y = Clamp(-player.speed * 60, player.speed * 60, player.velocity.y);
            player.velocity.x = Clamp(-player.speed * 60, player.speed * 60, player.velocity.x);
        }
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
                        if(cell.isActiveAndEnabled && CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), (cell.GetCollider())))
                        {
                            if(cell.allowBreaking && canMine)
                            {
                                // std::cout<<"Rectangle:"<<"X: "<<cell.GetCollider().x<<"Y: "<<cell.GetCollider().y<<"W: "<<cell.GetCollider().width<<"H: "<<cell.GetCollider().height<<std::endl;
                                cell.step += mineSpeed;
                                if(cell.step >= 10 && static_cast<OreTile>(cell.id) == mission.oreToMine)//cell is broken and the tile broken is the ore you are mining
                                {
                                    mission.quantity -= 1;//subtract one from the quantity
                                }
                                // break;
                            }
                            else if(static_cast<OreTile>(cell.id) == OreTile::ComputerOn)//check if is computer
                            {
                                cout << "Toggled computer screen" << endl;
                                // ToggleComputerScreen();
                                computerUI.isActiveAndEnabled = true;//only set to true, enter to escape it
                            }
                            else if(cell.id == 16)//check if is teleporter button
                            {
                                // field.clear();
                                if(objective == Objective::BeamDown && !computerUI.isActiveAndEnabled)//check if you went to the computer
                                {
                                    objective = Objective::CompleteMission;//change objective
                                    startAnimTime = (GetTime() * 60);
                                    showTeleportAnim = true;//show the teleporting animation
                                    ChangeScene(Scenes::Field);//change scene to asteroids
                                    continueLoop = false;//break from all FOR loops
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
            computerUI.isActiveAndEnabled = false;
        }
    }
    float halfW = player.sprite.width/2;
    float halfH = player.sprite.height/2;

    player.Update();

    Vector2 playerScreenPos = {floorf(player.transform.position.x / (GetScreenWidth() * 2)), floorf(player.transform.position.y / (GetScreenWidth() * 2))};
    Vector2 playerScreenPos2 = {floorf(player.transform.position.x / (GetScreenWidth() )), floorf(player.transform.position.y / (GetScreenWidth() ))};
    debugPosition = playerScreenPos;//debug
    if(playerScreenPos2.y >= voidDist)//player is in void
    {
        objective = Objective::VoidWarn1;
    }
    if(playerScreenPos2.y >= voidDist + 2)//player is in void, disable stars
    {
        objective = Objective::VoidWarn2;
    }
    if(playerScreenPos2.y >= voidDist  + 4)//player is in void, enable music
    {
        UpdateMusicStream(music);
        objective = Objective::VoidWarn3;
    }
    if(playerScreenPos2.y >= voidDist  + 6)//player is in purgatory
    {
        jumpscare = true;
        field.clear();
    }
    // cout << "X" << playerScreenPos.x << "Y" << playerScreenPos.y << endl;

    if(scene == Scenes::Field)
    {
        LoadSceneField(playerScreenPos, false);
    }

    if(mission.quantity <= 0)//mission complete
    {
        objective = Objective::ReturnToBase;
    }
    // else if (scene == 1)
    // {
    //     LoadStructureFromFile("test.grid");
    // }


    if(jumpscare)
    {
        UpdateMusicStream(music);
        UpdateMusicStream(staticMusic);
    }


    // asteroid.Update();


    if(!showDebug)
        camera.zoom = Clamp(0.5, 128, expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f)));
    else
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




//==================================
//      ALL NON-PUBLIC FUNCS
//==================================

void Manager::GenerateAsteroidsGrid(Vector2 positionInScreenWidthsTimesTwo)
{
    if(positionInScreenWidthsTimesTwo.y < voidDist/2)//     16 // 16 // 16
    {
        int rnd = GetScreenWidth()/2;
        // float gridX = GetScreenWidth();//480.0f;
        // float gridY = GetScreenHeight();
        int rx = GetRandomValue(-rnd, rnd);
        int ry = GetRandomValue(-rnd, rnd);
        Vector2 scvec = {(positionInScreenWidthsTimesTwo.x * GetScreenWidth()*2), (positionInScreenWidthsTimesTwo.y * GetScreenWidth()*2)};
        Vector2 vec = {rx + (positionInScreenWidthsTimesTwo.x * GetScreenWidth()*2), ry + (positionInScreenWidthsTimesTwo.y * GetScreenWidth()*2)};

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
    else
    {
        //void

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
    // cout<<"LoadSceneField ran"<<endl;
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
    int amountToMine = GetRandomValue(1, 6);
    int randomOre = GetRandomValue(0, 8);
    int isMeteorite = GetRandomValue(0, 100);
    switch(randomOre)
    {
        case 0://putin random
            randomMission.oreToMine = OreTile::Putin;
            amountToMine *= 8;
            randomMission.text = "Putonium";
            break;
        case 1:
            randomMission.oreToMine = OreTile::Meddorite;
            amountToMine *= 4;
            randomMission.text = "Meddorite";
            break;
        case 2:
            randomMission.oreToMine = OreTile::BlueOre;
            amountToMine *= 2;
            randomMission.text = "Lazurite";
            break;

        case 3:
            randomMission.oreToMine = OreTile::Maxium;
            amountToMine *= 5;
            randomMission.text = "Maxium";
            break;
        case 4:
            randomMission.oreToMine = OreTile::Trueblood;
            amountToMine *= 5;
            randomMission.text = "Truebloodium";
            break;
        case 5:
            randomMission.oreToMine = OreTile::Lucasite;
            amountToMine *= 5;
            randomMission.text = "Lucasite";
            break;
        case 6:
            randomMission.oreToMine = OreTile::Andreasite;
            amountToMine *= 5;
            randomMission.text = "Andreasite";
            break;
        case 7:
            randomMission.oreToMine = OreTile::Nathanium;
            amountToMine *= 5;
            randomMission.text = "Nathanium";
            break;
        case 8:
            randomMission.oreToMine = OreTile::HamOre;
            amountToMine *= 5;
            randomMission.text = "Hamzterzoid";
            break;
    }
    if(isMeteorite == 7)
    {
        randomMission.oreToMine = OreTile::MeteorCenter1;
        amountToMine  = 100;
        randomMission.text = "Meteorite";
    }
    randomMission.quantity = amountToMine;
    mission = randomMission;
}


void Manager::ToggleComputerScreen()
{
    // if(!computerUI.isActiveAndEnabled)
    computerUI.isActiveAndEnabled = !computerUI.isActiveAndEnabled;//toggle
}

void Manager::DrawAsteroidField()
{
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
                    if(cell.isActiveAndEnabled)
                        DrawRectangleRec(cell.GetCollider(), WHITE);//draw debug colliders
                }
            }
        }
}

void Manager::DrawDebugColls()
{
    if(showDebug)
    {
        DrawRectangleRec(player.GetCollider(), PURPLE);
        Vector2 worldPosButton = GetScreenToWorld2D({computerUI.GetButtonCollider().x, computerUI.GetButtonCollider().y}, camera);
        DrawRectangleRec({worldPosButton.x, worldPosButton.y, computerUI.GetButtonCollider().width, computerUI.GetButtonCollider().height}, RED);

    }
}

void Manager::DrawStarsBackground()
{
    if(player.transform.position.y < (voidDist + 2) * GetScreenWidth())//only spawn stars if outside of void
    {
        for(int i = 0; i < stars.size(); i++)
        {
            stars[i].Draw();
        } 
    }
}

void Manager::DrawTeleportAnimationFromTime()
{
    if(showTeleportAnim)//teleport animation logic
    {
        float curr = GetTime() * 60;//current time
        float animPlateauTimeL =  animPlateauTime; //+ animFadeTime/2;
        if(curr - startAnimTime <= animPlateauTimeL)//delta time between the start of anim and current time is < Plateau Time then draw full square
        {
            // if(curr - startAnimTime >= animFadeTime/2)
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            // else
            // {
            //     float val = (Clamp01((animFadeTime/2 - (curr - (startAnimTime + animPlateauTimeL))) / 60) * 255);
            //     DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {255, 255, 255, (unsigned char)val});
            // }
        }
        else //draw rect based on time since anim start + plateau time
        {
            float val = (Clamp01((animFadeTime - (curr - (startAnimTime + animPlateauTimeL))) / 60) * 255);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {255, 255, 255, (unsigned char)val});
            if(val <= 0)//end anim
            {
                showTeleportAnim = false;
            }
        }
    }
}

void Manager::SwitchObjectiveAndDraw()
{
    string str = "Find and Collect " + to_string(mission.quantity) + " " + mission.text;
    switch (objective)//draw objective in top left
    {
        case Objective::BeamDown:
            DrawTextEx(font, "Current Objective:", {10, 10}, 30, 3, WHITE);
            DrawTextEx(font, "Beam down to the Asteroid Belt", {10, 40}, 30, 3, {100, 100, 255, 255});//light blue
            break;
        case Objective::CompleteMission:
            // switch(mission.oreToMine)
            // {
            //     case OreTile::Putin:

            DrawTextEx(font, "Current Objective:", {10, 10}, 30, 3, WHITE);
            DrawTextEx(font, str.c_str(), {10, 40}, 30, 3, {180, 255, 180, 255});//light green
                    // break;
            // }
            break;
        case Objective::GoToComputer:
            DrawTextEx(font, "Current Objective:", {10, 10}, 30, 3, WHITE);
            DrawTextEx(font, "Go to the Computer to start the next mission", {10, 40}, 30, 3, WHITE);
            break;
        case Objective::ReturnToBase:
            DrawTextEx(font, "Current Objective:", {10, 10}, 30, 3, WHITE);
            DrawTextEx(font, "Return to the Mothership\n[Press F2]", {10, 40}, 30, 3, {255, 50, 50, 255});//light red
            break;
            

        case Objective::VoidWarn1:
            DrawTextEx(font, "WARNING:", {10, 10}, 30, 3, YELLOW);
            DrawTextEx(font, "Spatial anomalies detected in close proximity", {10, 40}, 30, 3, {255, 100, 100, 255});//light red
            break;
        case Objective::VoidWarn2:
            DrawTextEx(font, "FATAL ERR0R:", {10, 10}, 30, 3, {255, 100, 100, 255});
            DrawTextEx(font, "System Failure", {10, 40}, 50, 7, {255, 50, 50, 255});//light red
            break;
        case Objective::VoidWarn3:
            DrawTextEx(font, "0xE24F63C2", {10, 10}, 30, 15, RED);
            DrawTextEx(font, "TURN    BACK     NOW", {10, 40}, 40, 3, RED);//light red
            break;
        case Objective::Jumpscare:
            DrawTextEx(font, "  RETURN   TO   MOTHERSHIP  ?", {(float)((GetScreenWidth()-2320) / 2) + GetRandomValue(-16, 16), (float)((GetScreenHeight()-120)/2) + GetRandomValue(-16, 16)}, 120, 20, RED);//light red
            break;
    }
}

void Manager::SwitchPickaxeAndDraw()
{
    switch(player.pickaxe)
    {
        case PickaxeType::Default:
            DrawTextEx(font, "Current Pickaxe:", {10, (float)GetScreenHeight()-110}, 30, 3, WHITE);
            DrawTextEx(font, pickaxes[static_cast<int>(player.pickaxe)].name.c_str(), {10, (float)GetScreenHeight()-80}, 30, 3, WHITE);
            break;
        case PickaxeType::Epic:
            DrawTextEx(font, "Current Pickaxe:", {10, (float)GetScreenHeight()-110}, 30, 3, WHITE);
            DrawTextEx(font, pickaxes[static_cast<int>(player.pickaxe)].name.c_str(), {10, (float)GetScreenHeight()-80}, 30, 3, {180, 255, 180, 255});//light green
            break;
        case PickaxeType::Legendary:
            DrawTextEx(font, "Current Pickaxe:", {10, (float)GetScreenHeight()-110}, 30, 3, WHITE);
            DrawTextEx(font, pickaxes[static_cast<int>(player.pickaxe)].name.c_str(), {10, (float)GetScreenHeight()-80}, 30, 3, {255, 120, 255, 255});//light purple
            break;
        case PickaxeType::Wilbur:
            DrawTextEx(font, "Current Pickaxe:", {10, (float)GetScreenHeight()-110}, 30, 3, WHITE);
            DrawTextEx(font, pickaxes[static_cast<int>(player.pickaxe)].name.c_str(), {10, (float)GetScreenHeight()-80}, 30, 3, RED);//BLOOD RED
            break;
    }
}

void Manager::DrawMouseCursor()
{
    float mouseMagnitude = Distance({(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, mouse.position);
    if(mouseMagnitude > maxMineDist * 48 || jumpscare)//mouse is outside of mine distance
    {
        // DrawRectangle(mouseNormalized.x + (float)GetScreenWidth()/2, mouseNormalized.y + (float)GetScreenHeight()/2, 10, 10, WHITE);//Draw mouse cursor normalized
        DrawRectangle(mouse.position.x, mouse.position.y, 10, 10, {255, 0, 0, 127});//Draw mouse cursor out of range
        canMine = false;
    }
    else
    {
        DrawRectangle(mouse.position.x, mouse.position.y, 10, 10, WHITE);//Draw mouse cursor
        canMine = true;
    }
}
