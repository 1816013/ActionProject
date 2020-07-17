#include "Geometry.h"
#include <algorithm>
#include <DxLib.h>

float Dot(const Vector2f& va, const Vector2f& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

float Clamp(float val, float minVal, float maxVal)
{
	return max(minVal,min(maxVal, val));
}
