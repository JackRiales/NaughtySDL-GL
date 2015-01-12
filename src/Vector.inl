#include "Vector.hpp"

template <typename T>
Vector2D<T>& Vector2D<T>::operator=(const Vector2D& arg)
{
    x = arg.x;
    y = arg.y;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator=(const T& arg)
{
    x = arg;
    y = arg;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator+(const Vector2D& arg)
{
    x += arg.x;
    y += arg.y;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator+(const T& arg)
{
    x = arg;
    y = arg;
    return *this;
}
