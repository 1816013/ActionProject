#include "CapsuleCollider.h"
#include "CircleCollider.h"
#include <cassert>
#include <DxLib.h>
#include "../Character.h"
#include "../Camera.h"

CapsuleCollider::CapsuleCollider(std::shared_ptr<Character> owner, const char* tag, bool immortal)
	: Collider(owner, tag, immortal)
{
}

CapsuleCollider::CapsuleCollider(std::shared_ptr<Character> owner, const Capsule& cap, const char* tag, bool immortal) :
	Collider(owner, tag, immortal),
	capsule_(cap)
{
}

bool CapsuleCollider::IsHit(std::shared_ptr<Collider> col)
{
	assert(col != nullptr);
	if (capsule_.seg.vec.SQMagnitude() == 0)
	{
		return false;
	}
	auto cCol = std::dynamic_pointer_cast<CircleCollider>(col);
	if (cCol != nullptr)
	{
		Capsule capsule = { {AcutualPosition(), capsule_.seg.vec}, capsule_.radius };
		Circle circle = { cCol->AcutualPosition(), cCol->GetCircle().radius };
		auto vecA = circle.center - capsule.seg.start;
		
		float sqDist = (vecA - (capsule.seg.vec * Clamp(Dot(vecA, capsule.seg.vec) / capsule.seg.vec.SQMagnitude()))).SQMagnitude();
		auto totalRadius = capsule.radius + circle.radius;	// 半径の合計
		return  sqDist <= totalRadius * totalRadius;
	}
	return false;
}

void CapsuleCollider::Draw(std::shared_ptr<Camera>c)
{
	if (OwnerIsDead())return;
	auto offset = c->ViewOffset();
	if (capsule_.seg.vec.SQMagnitude() == 0)return;
	Capsule capsule = { {AcutualPosition(), capsule_.seg.vec }, capsule_.radius};
	auto& spos = capsule.seg.start;
	auto epos = capsule.seg.start + capsule.seg.vec ;

	int posnum = 32; // DrawCircleAAの頂点数
	DrawCircleAA(spos.x + offset.x, spos.y, capsule.radius, posnum, 0xffffff, false);
	
	auto v90 = capsule.seg.vec;
	v90 = {-v90.y, v90.x};
	v90.Nomarize();
	v90 *= capsule.radius;

	auto p1 = spos + v90;	// 左上
	auto p2 = epos + v90;	// 右上
	auto p3 = epos - v90;	// 右下
	auto p4 = spos - v90;	// 左下
	DrawQuadrangleAA(p1.x + offset.x, p1.y, p2.x + offset.x, p2.y, p3.x + offset.x, p3.y, p4.x + offset.x, p4.y, 0xffffff, false);

	DrawCircleAA(epos.x + offset.x, epos.y, capsule.radius, posnum, 0xffffff, false);
}

const Vector2f CapsuleCollider::AcutualPosition()
{
	auto owner = GetOwner();
	/*if (owner == nullptr)
	{
		return Vector2f::ZERO;
	}*/
	return capsule_.seg.start + GetOwner()->GetPosition();
}

Capsule& CapsuleCollider::GetCapsule()
{
	return capsule_;
}
