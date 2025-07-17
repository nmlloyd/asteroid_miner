#include <raylib.h>
#include <vector>
#include "asteroid.hpp"
#include "star.hpp"

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
        int rnd = 30;
        void DestroyInactiveStars();
        // float gridX; //= 123.0f;
        // float gridY;// = 123.0f;
        // int rx ;//= GetRandomValue(-rnd, rnd);
        // int ry ;//= GetRandomValue(-rnd, rnd);
        std::vector<Star> stars;
};
