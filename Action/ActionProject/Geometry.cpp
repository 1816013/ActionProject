#include "Geometry.h"
#include <algorithm>
#include <DxLib.h>

 const Vector2D<float> Vector2D<float>::ZERO(0.0f, 0.0f);
 const Vector2D<float> Vector2D<float>::NIL(NAN, NAN);

float Dot(const Vector2f& va, const Vector2f& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

float Clamp(float val, float minVal, float maxVal)
{
	return min(max(val, minVal), maxVal);
}
