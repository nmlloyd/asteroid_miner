#include <iostream>
#include <raylib.h>
#include <vector>
#include "button.hpp"

using namespace std;

class Shope{
    private:
    std::vector<Button> buttons;
    static Texture2D sprite;
    Rectangle backplate;

    public:
    Shope(Vector2 pos);
    
    void update();
    void draw();

};
