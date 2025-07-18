#pragma once
#include <raylib.h>

struct Transform2D
{
    Vector2 position;
    float rotation;
    float scale;
};
struct ShadingPixel
{
    Vector2 position;
    float alpha = 1; // 0 to 1
};
struct Vector2Bool //a struct with a point and a boolean
{
    float x;
    float y;
    bool boolean;
};
// struct Vector2D {//an expanded Vector2 struct
//     float x, y;

//     // Vector subtraction
//     Vector2D operator-(const Vector2D& other) const {
//         return {x - other.x, y - other.y};
//     }

//     // Scalar multiplication
//     Vector2D operator*(float scalar) const {
//         return {x * scalar, y * scalar};
//     }

//     // Vector addition
//     Vector2D operator+(const Vector2D& other) const {
//         return {x + other.x, y + other.y};
//     }

//     // Dot product
//     float dot(const Vector2D& other) const {
//         return x * other.x + y * other.y;
//     }

//     // Normalize
//     Vector2D normalize() const {
//         float len = std::sqrt(x * x + y * y);
//         return {x / len, y / len};
//     }

//     void print() const {
//         std::cout << "(" << x << ", " << y << ")\n";
//     }
// };

// Vector2D reflect(const Vector2D& v, const Vector2D& normal) {
//     Vector2D n = normal.normalize(); // Ensure the normal is unit length
//     return v - n * (2.0f * v.dot(n));
// }