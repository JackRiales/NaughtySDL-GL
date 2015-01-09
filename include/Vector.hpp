#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T = int>
struct Vector2D
{
    Vector2D (T _x = 0, T _y = 0) : x (_x), y (_y) { ; }
    T   x;
    T   y;
};

template <typename T = int>
struct Vector3D
{
    Vector3D (T _x = 0, T _y = 0, T _z = 0) : x (_x), y (_y), z (_z) { ; }
    T   x;
    T   y;
    T   z;
};

template <int points, typename T = int>
struct Vector
{
    Vector () { ; }
    Vector ( T** point_array ) { point = point_array; }
    T   point [ points ];
};

#endif // VECTOR_HPP
