#include <raylib.h>
#include "cell.hpp"
#include <vector>

class Asteroid
{
    public:
        Asteroid();
        ~Asteroid();
        void Update();
        void Draw();
        Vector2 position;
    private:
        std::vector<Cell> cells; //4x4
        std::vector<std::vector<int>> grid;
};