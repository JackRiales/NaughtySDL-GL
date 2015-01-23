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
    Vector2D& operator+(Vector2D* arg);
    Vector2D& operator+(const T& arg);
};

typedef Vector2D<int>       iVector2D;
typedef Vector2D<float>     fVector2D;
typedef Vector2D<double>    dVector2D;

#include "../src/Vector.inl"

#endif // VECTOR_HPP
