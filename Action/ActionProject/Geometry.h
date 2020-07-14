#pragma once
#include <cmath>

template<typename T>
struct Vector2D
{
	T x;
	T y;
	Vector2D() : x(0), y(0) {};
	Vector2D(T inx, T iny) : x(inx), y(iny){};
	Vector2D operator+(const Vector2D& val)const
	{
		return Vector2D(x + val.x, y + val.y);
	}

	Vector2D operator-(const Vector2D& val)const
	{
		return Vector2D(x - val.x, y - val.y);
	}

	Vector2D operator/(const float& scale)const
	{
		return Vector2D(x / scale, y / scale);
	}

	void operator+=(const Vector2D& val)
	{
		x += val.x;
		y += val.y;
	}

	void operator-=(const Vector2D& val)
	{
		x -= val.x;
		y -= val.y;
	}

	void operator*=(const float& scale)
	{
		x *= scale;
		y *= scale;
	}

	float Magnitude()const
	{
		return hypot(x, y);
	}

	/// <summary>
	///  ベクトルの長さの2乗を返す
	/// </summary>
	/// <returns> ベクトルの長さの2乗</returns>
	float SQMagnitude()const
	{
		return x * x + y * y;
	}

	void Nomarize()
	{
		Vector2D vec(x, y);
		auto mag = vec.Magnitude();
		x /= mag;
		y /= mag;
	}

	Vector2D Nomarized()
	{
		Vector2D vec(x, y);
		auto mag = vec.Magnitude();
		return (x / mag, y / mag);
	}

};


using Vector2 = Vector2D<int>;
using Vector2f = Vector2D<float>;
using Position2 = Vector2;
using Position2f = Vector2f;

struct Size
{
	int w, h;
	Size() : w(0), h(0) {};
	Size(int vw, int vh) :w(vw), h(vh) {};
};

struct Rect 
{
	Position2 pos;
	Size size;
	Rect(const Position2& vpos, const Size& vsize) : pos(vpos),size(vsize){};
	int Left()const
	{
		return pos.x - size.w / 2;
	}
	int Right()const
	{
		return pos.x + size.w / 2;
	}
	int Top()const
	{
		return pos.y - size.h / 2;
	}
	int Bottom()const
	{
		return pos.y + size.h / 2;
	}
};

/// <summary>
/// 円
/// </summary>
struct Circle
{
	Position2f center;	// 中心
	float radius;		// 半径
	Circle() :center({ 0, 0 }), radius(0.0f) {}
	Circle(const Position2f& c, const float r) :center(c), radius(r) {}
};