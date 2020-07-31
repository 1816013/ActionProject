#pragma once
#include <cmath>
#include <cassert>

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

	Vector2D operator*(const float scale)const
	{
		return Vector2D(x * scale, y * scale);
	}

	Vector2D operator/(const float scale)const
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

	bool operator==(const Vector2D& v)
	{
		//assert(!(isnan(v.x) && isnan(v.y)));
		return x == v.x && y == v.y;
	}

	bool operator!=(const Vector2D& v)
	{
		//assert(!(isnan(v.x) && isnan(v.y)));
		return !(x == v.x && y == v.y);
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
		assert(mag != 0.0f);
		x /= mag;
		y /= mag;
	}

	const Vector2D Nomarized() const
	{
		Vector2D vec(x, y);		
		auto mag = vec.Magnitude();
		assert(mag != 0.0f);
		return Vector2D(x / mag, y / mag);
	}

	bool IsNil()const
	{
		return isnan(x) || isnan(y);
	}

	static const Vector2D<float>ZERO;
	static const Vector2D<float>NIL;
};


using Vector2 = Vector2D<int>;
using Vector2f = Vector2D<float>;
using Position2 = Vector2;
using Position2f = Vector2f;

float Dot(const Vector2f& va, const Vector2f& vb);

float Closs(const Vector2f& va, const Vector2f& vb);

float Clamp(float val, float minVal = 0.0f, float maxVal = 1);

struct Size
{
	int w, h;
	Size() : w(0), h(0) {};
	Size(int vw, int vh) :w(vw), h(vh) {};
};

struct Rect 
{
	Position2f pos;	// 中心座標
	Size size;		// 大きさ
	Rect() : pos({ 0, 0 }), size({ 0, 0 }) {};
	Rect(const Position2f& vpos, const Size& vsize) : pos(vpos),size(vsize){};
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
/// <summary>
/// 線分
/// </summary>
struct Segment
{
	Position2f start;
	Vector2f vec;

	Segment() :start({ 0, 0 }), vec({ 0, 0 }) {};
	Segment(Position2f s, Vector2f v) : start(s), vec(v) {};
	Segment(float x, float y, float vx, float vy) : start(x, y), vec(vx, vy) {};

	static const Segment ZERO;
	static const Segment NIL;
	bool IsNil();
	Position2f End();
};

/// <summary>
/// カプセル
/// </summary>
struct Capsule
{
	Segment seg;	// 線分
	//Position2f start;	// 起点
	//Vector2f vecEnd;	// 起点から端点のベクトル
	float radius;	// 半径

	Capsule() : seg({ {0, 0}, { 0, 0 } })/*,start({ 0, 0 }), vecEnd({ 0, 0 })*/, radius(0.0f) {};
	//Capsule(const Position2f& s, const Vector2f& v, const float r) : start(s), vecEnd(v), radius(r) {};
	Capsule(const Segment& s, const float r) :seg(s), radius(r) {};
};