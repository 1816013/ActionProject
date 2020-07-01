#pragma once

template<typename T>
struct Vector2D
{
	T x;
	T y;
	Vector2D() : x(0), y(0) {};
	Vector2D(T inx, T iny) : x(inx), y(iny){};
	Vector2D operator+(const Vector2D& val)
	{
		return Vector2D(x + val.x, y + val.y);
	}

	Vector2D operator-(const Vector2D& val)
	{
		return Vector2D(x - val.x, y - val.y);
	}

};


using Vector2 = Vector2D<int>;
using Vector2F = Vector2D<float>;
using Position2 = Vector2;
using Position2f = Vector2F;

struct Size
{
	int w, h;
};

struct Rect 
{
	Position2 pos;
	Size size;
};