#include <raylib.h>

class Cell
{
    public:
        Cell();
        //~Cell();
        void Draw();
        void DrawOutlines();
        Vector2 GetUnitSize();
        Rectangle GetCollider();
        Vector2 position;
        int id = 2;
        static Texture2D unitTex[8];
};