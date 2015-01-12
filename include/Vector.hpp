#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T = int>
struct Vector2D
{
    Vector2D (T _x = 0, T _y = 0) : x (_x), y (_y) { ; }
    T   x;
    T   y;

    Vector2D& operator=(const Vector2D& arg);
    Vector2D& operator=(const T& arg);

    Vector2D& operator+(const Vector2D& arg);
    Vector2D& operator+(const T& arg);
};

template <typename T = int>
struct Vector3D
{
    Vector3D (T _x = 0, T _y = 0, T _z = 0) : x (_x), y (_y), z (_z) { ; }
    T   x;
    T   y;
    T   z;
};

#include "../src/Vector.inl"

#endif // VECTOR_HPP
