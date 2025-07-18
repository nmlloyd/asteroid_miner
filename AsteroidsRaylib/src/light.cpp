#include "light.hpp"

Light::Light()
{

}

Light::Light(Vector2 pos, double thresh, float r)
{
    position = pos;
    threshold = thresh;
    radiusInPixels = r;
}