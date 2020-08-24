#include "Geometry.h"
#include <algorithm>
#include <DxLib.h>

 const Vector2D<float> Vector2D<float>::ZERO(0.0f, 0.0f);
 const Vector2D<float> Vector2D<float>::NIL(NAN, NAN);
 const Vector2D<float> Vector2D<float>::UP(0.0f, -1.0f);
 const Vector2D<float> Vector2D<float>::DOWN(0.0f, 1.0f);
 const Vector2D<float> Vector2D<float>::RIGHT(1.0f, 0.0f);
 const Vector2D<float> Vector2D<float>::LEFT(-1.0f, 0.0f);

 const Segment Segment::ZERO(Vector2f::ZERO, Vector2f::ZERO);
 const Segment Segment::NIL(Vector2f::NIL, Vector2f::NIL);

float Dot(const Vector2f& va, const Vector2f& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

float Closs(const Vector2f& va, const Vector2f& vb)
{
    return va.y * vb.x - va.x * vb.y;
}

float Clamp(float val, float minVal, float maxVal)
{
	return min(max(val, minVal), maxVal);
}

bool Segment::IsNil()
{
    return isnan(vec.x) || isnan(vec.y);
}

Position2f Segment::End()
{
    return start + vec;
}
