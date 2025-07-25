#include <iostream>
#include <raylib.h>
#include <vector>
#include "button.hpp"

using namespace std;

class Shope{
    private:
    bool isOpen;
    
    static Texture2D sprite;
    Rectangle backplate;

    public:

    vector<Button> buttons;
    Shope();
    
    void update();
    void draw();

    bool getOverlayState();
    void setShop(bool state);
    void toggleShop();

};
