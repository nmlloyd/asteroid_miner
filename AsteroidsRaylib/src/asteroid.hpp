#include <raylib.h>

class Asteroid
{
    public:
        Asteroid();
        Asteroid(Vector2 position, Texture2D unitTex);
        ~Asteroid();
        void Update();
        void Draw();
        Vector2 position;
        Texture2D unitTex;
};