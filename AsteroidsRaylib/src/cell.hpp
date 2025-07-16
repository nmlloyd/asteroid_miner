#include <raylib.h>

class Cell
{
    public:
        Cell();
        ~Cell();
        void Draw();
        Vector2 GetUnitSize();
        Vector2 position;
        static Texture2D unitTex;
};