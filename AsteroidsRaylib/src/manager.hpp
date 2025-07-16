#include <raylib.h>
#include "asteroid.hpp"

class Manager
{
    public:
        Manager();
        void Start();
        void Update();
    private:
        Asteroid asteroid;
};
