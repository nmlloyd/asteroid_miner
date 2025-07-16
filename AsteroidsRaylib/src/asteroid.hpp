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
        std::vector<Cell> cells; //4x4
    private:
        // std::vector<std::vector<int>> grid;
        std::vector<Vector2> Generate(int r);
        std::vector<Vector2> MidPointCircleDraw(int xcenter, int ycenter, int r);
        std::vector<Vector2> drawcircle(int xc,int yc,int x,int y);
        bool IsInsideCircle(Vector2 point, int xcenter, int ycenter, int r);
};