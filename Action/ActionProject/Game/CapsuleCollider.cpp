#include "CapsuleCollider.h"
#include "CircleCollider.h"
#include <cassert>
#include <DxLib.h>
#include "Character.h"

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
	if (capsule_.vecEnd.SQMagnitude() == 0)
	{
		return false;
	}
	auto cCol = std::dynamic_pointer_cast<CircleCollider>(col);
	if (cCol != nullptr)
	{
		Capsule capsule = { AcutualPosition(), capsule_.vecEnd, capsule_.radius };
		Circle circle = { cCol->AcutualPosition(), cCol->GetCircle().radius };
		auto vecA = circle.center - capsule.start;
		
		float sqDist = (vecA - (capsule.vecEnd * Clamp(Dot(vecA, capsule.vecEnd) / capsule.vecEnd.SQMagnitude()))).SQMagnitude();
		auto totalRadius = capsule.radius + circle.radius;	// îºåaÇÃçáåv
		return  sqDist <= totalRadius * totalRadius;
	}
	return false;
}

void CapsuleCollider::Draw()
{
	if (capsule_.vecEnd.SQMagnitude() == 0)
	{
		return;
	}
	Capsule capsule = { AcutualPosition(), capsule_.vecEnd , capsule_.radius };
	auto& spos = capsule.start;
	auto epos = capsule.start + capsule.vecEnd ;

	DrawCircle(spos.x, spos.y, capsule.radius, 0xffffff, false);
	
	auto v90 = capsule.vecEnd;
	v90 = {-v90.y, v90.x};
	v90.Nomarize();
	v90 *= capsule.radius;

	auto p1 = spos + v90;	// ç∂è„
	auto p2 = epos + v90;	// âEè„
	auto p3 = epos - v90;	// âEâ∫
	auto p4 = spos - v90;	// ç∂â∫
	DrawQuadrangleAA(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, 0xffffff, false);

	DrawCircle(epos.x, epos.y, capsule.radius, 0xffffff, false);
}

const Vector2f CapsuleCollider::AcutualPosition()
{
	return capsule_.start + GetOwner()->GetPosition();
}

Capsule& CapsuleCollider::GetCapsule()
{
	return capsule_;
}
