#include <raylib.h>
#include "player.hpp"

class Star
{
    public:
        Star();

        int offscreenDirection; //0 = left; 1 = right; 2 = up;S 3 = down
        Vector2 position;
        Player player;
        bool isActive;
        void DestroyInactiveStars();
        void Update();
        void Draw();
    private:
        ;
};