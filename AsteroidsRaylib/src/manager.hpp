#include <raylib.h>
#include "asteroid.hpp"
#include "player.hpp"

class Manager
{
    public:
        Manager();
        void Draw();
        void Start();
        void Update();
    private:
        Asteroid asteroid;
        Camera2D camera;
        Player player;
};
