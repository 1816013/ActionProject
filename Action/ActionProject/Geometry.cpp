#include "Geometry.h"
#include <algorithm>
#include <DxLib.h>
#include <vector>

 const Vector2D<float> Vector2D<float>::ZERO(0.0f, 0.0f);
 const Vector2D<float> Vector2D<float>::NIL(NAN, NAN);
 const Vector2D<float> Vector2D<float>::UP(0.0f, -1.0f);
 const Vector2D<float> Vector2D<float>::DOWN(0.0f, 1.0f);
 const Vector2D<float> Vector2D<float>::RIGHT(1.0f, 0.0f);
 const Vector2D<float> Vector2D<float>::LEFT(-1.0f, 0.0f);

 const Segment Segment::ZERO(Vector2f::ZERO, Vector2f::ZERO);
 const Segment Segment::NIL(Vector2f::NIL, Vector2f::NIL);

 namespace DxLib
 {
	 const tagVECTOR& V2V(const Vector2f& v)
	 {
		 return VGet(v.x, v.y, 0.0f);
	 }
 }

float Dot(const Vector2f& va, const Vector2f& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

float Closs(const Vector2f& va, const Vector2f& vb)
{
    return va.x * vb.y - va.y * vb.x;
}

float Clamp(float val, float minVal, float maxVal)
{
	return min(max(val, minVal), maxVal);
}

float GetAngle2Vector(const Vector2f& v1, const Vector2f& v2)
{
    auto nv1 = v1.Nomarized();
    auto nv2 = v2.Nomarized();
    float dot = Dot(nv1, nv2);	// cosθｘ
    float closs = Closs(nv1, nv2); //sinθｙ
    auto angle = atan2(closs, dot);
    if (angle < 0.0f)
    {
        angle += DX_PI_F * 2.0f;
    }
    return angle;
}

bool Segment::IsNil()
{
    return isnan(vec.x) || isnan(vec.y);
}

Position2f Segment::End()
{
    return start + vec;
}

FanShape::FanShape(const Position2f& p, const Vector2f& inv1, const Vector2f& inv2)
: center(p), v1(inv1), v2(inv2)
{
}

FanShape::FanShape(const Position2f& p, const Vector2f& inv1, float angle)
    : center(p), v1(inv1)
{
	v2 = RotateMat(angle)* v1;
}

void FanShape::Draw(int graphH, float amp, bool distF, unsigned int color)
{
	constexpr float step_angle = (DX_PI_F / 18.0f);
	float angleRange = GetAngle2Vector(v1, v2);
	size_t triangleNum = static_cast<size_t>(angleRange / step_angle);
	// 割り切れるか
	float rem = fmod(angleRange, step_angle);
	auto remNum = rem > 0 ? triangleNum + 1 : triangleNum;

	std::vector<VERTEX2D> vertices(3 * remNum);
	for (auto& v : vertices)
	{
		v.dif.r = 0xaa;
		v.dif.g = 0xaa;
		v.dif.b = 0xff;
		v.dif.a = 0xaa;
		v.u = 0.0f;
		v.v = 0.0f;
		v.rhw = 1.0f;
	}
	Vector2f tmpV1 = v1;
	Vector2f tmpV2 = RotateMat(step_angle) * tmpV1;
	auto ampX = amp / 800;
	auto ampY = amp / 600;
	for (size_t i = 0; i < triangleNum; ++i)
	{
		vertices[i * 3 + 0].pos = V2V(center);
		vertices[i * 3 + 0].u = vertices[i * 3 + 0].pos.x / 800.f;
		vertices[i * 3 + 0].v = vertices[i * 3 + 0].pos.y / 600.f;
		vertices[i * 3 + 1].pos = V2V(center + tmpV1);
		vertices[i * 3 + 1].u = sin(float(i * step_angle)) * ampX + vertices[i * 3 + 1].pos.x / 800.f;
		vertices[i * 3 + 1].v = sin(float(i * step_angle)) * ampY + vertices[i * 3 + 1].pos.y / 600.f;
		vertices[i * 3 + 2].pos = V2V(center + tmpV2);
		vertices[i * 3 + 2].u = sin(float(i * step_angle)) * ampX + vertices[i * 3 + 2].pos.x / 800.f;
		vertices[i * 3 + 2].v = sin(float(i * step_angle)) * ampY + vertices[i * 3 + 2].pos.y / 600.f;
		tmpV1 = tmpV2;
		tmpV2 = RotateMat(step_angle) * tmpV1;
	}
	// step_angleで割り切れないときの表示
	tmpV2 = v2;
	if (rem > 0.0f)
	{
		vertices[triangleNum * 3 + 0].pos = V2V(center);
		vertices[triangleNum * 3 + 0].u = /*cos(float(triangleNum * step_angle)) * ampX + */vertices[triangleNum * 3 + 0].pos.x / 800.f;
		vertices[triangleNum * 3 + 0].v = /*cos(float(triangleNum * step_angle)) * ampY + */vertices[triangleNum * 3 + 0].pos.y / 600.f;
		vertices[triangleNum * 3 + 1].pos = V2V(center + tmpV1);
		vertices[triangleNum * 3 + 1].u = sin(float(triangleNum * step_angle)) * ampX + vertices[triangleNum * 3 + 1].pos.x / 800.f;
		vertices[triangleNum * 3 + 1].v = sin(float(triangleNum * step_angle)) * ampY + vertices[triangleNum * 3 + 1].pos.y / 600.f;
		vertices[triangleNum * 3 + 2].pos = V2V(center + tmpV2);
		vertices[triangleNum * 3 + 2].u = sin(float(triangleNum * step_angle)) * ampX + vertices[triangleNum * 3 + 2].pos.x / 800.f;
		vertices[triangleNum * 3 + 2].v = sin(float(triangleNum * step_angle)) * ampY + vertices[triangleNum * 3 + 2].pos.y / 600.f;
		tmpV1 = tmpV2;
		tmpV2 = RotateMat(step_angle) * tmpV1;
	}

	//v.emplace_back({center.x, center.y}, 1.0f, );
	if (graphH == -1)
	{
		graphH = DX_NONE_GRAPH;
	}
	DrawPrimitive2D(vertices.data(), vertices.size(), DX_PRIMTYPE_TRIANGLELIST, graphH, false);
	DrawLineAA(center.x, center.y,
		(center + v1).x, (center + v1).y, 0xff0000, 3.0f);
	DrawLineAA(center.x, center.y,
		(center + v2).x, (center + v2).y, 0xff0000, 3.0f);
}

float FanShape::Radius() const
{
	return 0.0f;
}

void FanShape::AddAngle1(float angle)
{
    float tmpAngle = GetAngle2Vector(v1, v2);
    v2 = RotateMat(tmpAngle + angle) * v1;
}

void FanShape::AddAngle2(float angle)
{
}

float FanShape::GetAngle() const
{
	return 0.0f;
}


// 単位行列を返す
Matrix IdentityMat() {
	Matrix ret = {};		// 0で初期化
	ret.m[0][0] = ret.m[1][1] = ret.m[2][2] = 1.0f;
	return ret;
}

// ２つの行列の乗算を返す
Matrix MultipleMat(const Matrix& lmat, const Matrix& rmat) {
	Matrix ret = {  };
	ret.m[0][0] = lmat.m[0][0] * rmat.m[0][0] + lmat.m[0][1] * rmat.m[1][0] + lmat.m[0][2] * rmat.m[2][0];
	ret.m[0][1] = lmat.m[0][0] * rmat.m[0][1] + lmat.m[0][1] * rmat.m[1][1] + lmat.m[0][2] * rmat.m[2][1];
	ret.m[0][2] = lmat.m[0][0] * rmat.m[0][2] + lmat.m[0][1] * rmat.m[1][2] + lmat.m[0][2] * rmat.m[2][2];
	ret.m[1][0] = lmat.m[1][0] * rmat.m[0][0] + lmat.m[1][1] * rmat.m[1][0] + lmat.m[1][2] * rmat.m[2][0];
	ret.m[1][1] = lmat.m[1][0] * rmat.m[0][1] + lmat.m[1][1] * rmat.m[1][1] + lmat.m[1][2] * rmat.m[2][1];
	ret.m[1][2] = lmat.m[1][0] * rmat.m[0][2] + lmat.m[1][1] * rmat.m[1][2] + lmat.m[1][2] * rmat.m[2][2];
	ret.m[2][0] = lmat.m[2][0] * rmat.m[0][0] + lmat.m[2][1] * rmat.m[1][0] + lmat.m[2][2] * rmat.m[2][0];
	ret.m[2][1] = lmat.m[2][0] * rmat.m[0][1] + lmat.m[2][1] * rmat.m[1][1] + lmat.m[2][2] * rmat.m[2][1];
	ret.m[2][2] = lmat.m[2][0] * rmat.m[0][2] + lmat.m[2][1] * rmat.m[1][2] + lmat.m[2][2] * rmat.m[2][2];
	return ret;

}

// ベクトルに対して行列乗算を適用し、結果のベクトルを返す
Vector2f MultipleVec(const Matrix& mat, const Vector2f& vec) {
	Vector2f ret = {};
	ret.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2];
	ret.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2];
	return ret;
}

Vector2f operator*(const Matrix& mat, const Vector2f& vec)
{
	return MultipleVec(mat, vec);
}

// 平行移動行列を返す
Matrix TranslateMat(float x, float y) {
	Matrix ret = {};
	ret = IdentityMat();
	ret.m[0][2] = x;
	ret.m[1][2] = y;
	return ret;
}

///回転行列を返す
///@param angle 回転角度
Matrix RotateMat(float angle) {
	Matrix ret = {};
	ret = IdentityMat();
	ret.m[0][0] = cos(angle);
	ret.m[0][1] = -sin(angle);
	ret.m[1][0] = sin(angle);
	ret.m[1][1] = cos(angle);
	return ret;
}

SlashShape::SlashShape(const Position2f& p, const Vector2f& inv1, const Vector2f& inv2)
	: center(p), v1(inv1), v2(inv2)
{
}

SlashShape::SlashShape(const Position2f& p, const Vector2f& inv1, float angle)
	: center(p), v1(inv1)
{
	v2 = RotateMat(angle) * v1;
}

void SlashShape::Draw(int graphH, float amp, bool distF, unsigned int color)
{
	
	constexpr float step_angle = (DX_PI_F / 18.0f);
	float angleRange = GetAngle2Vector(v1, v2);
	size_t triangleNum = static_cast<size_t>(angleRange / step_angle);
	// 割り切れるか
	float rem = fmod(angleRange, step_angle);
	auto remNum = rem > 0 ? triangleNum + 1 : triangleNum;

	std::vector<VERTEX2D> vertices(2 * remNum);
	for (auto& v : vertices)
	{
		v.dif.r = 0xaa;
		v.dif.g = 0xaa;
		v.dif.b = 0xff;
		v.dif.a = 0xaa;
		v.u = 0.0f;
		v.v = 0.0f;
		v.rhw = 1.0f;
	}

	Vector2f tmpV = v1;
	auto r = tmpV.Magnitude();
	auto inr = r;
	auto stepr = r / (float)(triangleNum + 1);
	auto ampX = amp / 800;
	auto ampY = amp / 600;
	for (size_t i = 0; i < triangleNum; ++i)
	{
		auto nv = tmpV.Nomarized();
		vertices[i * 2 + 0].pos = V2V(center + nv * inr );
		vertices[i * 2 + 0].u = vertices[i * 2 + 0].pos.x / 800.f;
		vertices[i * 2 + 0].v = vertices[i * 2 + 0].pos.y / 600.f;
		vertices[i * 2 + 1].pos = V2V(center + nv * r);
		vertices[i * 2 + 1].u = cos(float(i * step_angle)) * ampX + vertices[i * 2 + 1].pos.x / 800.f;
		vertices[i * 2 + 1].v = sin(float(i * step_angle)) * ampY + vertices[i * 2 + 1].pos.y / 600.f;
		tmpV = RotateMat(step_angle) * tmpV;
		inr = inr - stepr;
		inr = max(inr, 0);
	}
	// step_angleで割り切れないときの表示
	tmpV = v2;
	if (rem > 0.0f)
	{
		auto nv = tmpV.Nomarized();
		vertices[triangleNum * 2 + 0].pos = V2V(center + nv * inr);
		vertices[triangleNum * 2 + 0].u = vertices[triangleNum * 2 + 0].pos.x / 800.f;
		vertices[triangleNum * 2 + 0].v = vertices[triangleNum * 2 + 0].pos.y / 600.f;
		vertices[triangleNum * 2 + 1].pos = V2V(center + nv * r);
		vertices[triangleNum * 2 + 1].u = cos(float(triangleNum * step_angle)) * ampX + vertices[triangleNum * 2 + 1].pos.x / 800.f;
		vertices[triangleNum * 2 + 1].v = sin(float(triangleNum * step_angle)) * ampY + vertices[triangleNum * 2 + 1].pos.y / 600.f;
		tmpV = RotateMat(step_angle) * tmpV;
	}

	//v.emplace_back({center.x, center.y}, 1.0f, );
	if (graphH == -1)
	{
		graphH = DX_NONE_GRAPH;
	}
	DrawPrimitive2D(vertices.data(), vertices.size(), DX_PRIMTYPE_TRIANGLESTRIP, graphH, false);
	DrawLineAA(center.x, center.y,
		(center + v1).x, (center + v1).y, 0xff0000, 3.0f);
	DrawLineAA(center.x, center.y,
		(center + v2).x, (center + v2).y, 0xff0000, 3.0f);
}

float SlashShape::Radius() const
{
	return 0.0f;
}

void SlashShape::AddAngle1(float angle)
{
	float tmpAngle = GetAngle2Vector(v1, v2);
	v2 = RotateMat(tmpAngle + angle) * v1;
}

void SlashShape::AddAngle2(float angle)
{
}

float SlashShape::GetAngle() const
{
	return 0.0f;
}
