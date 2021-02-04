#include "FanCollider.h"
#include <DxLib.h>
#include <cassert>
#include "../Character.h"
#include "CircleCollider.h"

FanCollider::FanCollider(std::shared_ptr<Character> owner, const char* tag, bool immortal):
	Collider(owner, tag, immortal),
	isAttack_(false)
{
}

FanCollider::FanCollider(std::shared_ptr<Character> owner, const FanShape& fan, const char* tag, bool immortal) :
	Collider(owner, tag, immortal),
	fanShape_(fan),
	isAttack_(false)
{

 }

bool FanCollider::IsHit(std::shared_ptr<Collider> col)
{
	if (!isAttack_)
	{
		return false;
	}
	assert(col != nullptr);
	auto cCol = std::dynamic_pointer_cast<CircleCollider>(col);
	if (fanShape_.v1 == fanShape_.v2)return false;
	if (cCol != nullptr)
	{
		FanShape fan = { AcutualPosition(), fanShape_.v1, fanShape_.v2 };
		Circle c = { cCol->AcutualPosition(), cCol->GetCircle().radius };

		float diff = (c.center - fan.center).Magnitude();
		if (diff > fan.Radius() + c.radius)return false;
		auto v = (c.center - fan.center);
		auto betAngle = fan.GetAngle();
		if (GetAngle2Vector(fan.v1, v) < betAngle){
			return true;
		}
		if ((v - fan.v1 * Clamp(Dot(v, fan.v1) / fan.v1.SQMagnitude())).Magnitude() <= c.radius)
		{
			return true;
		}
		if ((v - fan.v2 * Clamp(Dot(v, fan.v2) / fan.v2.SQMagnitude())).Magnitude() <= c.radius)
		{
			return true;
		}
		return false;
	}
	return false;
}

void FanCollider::Draw(std::shared_ptr<Camera> c)
{
	DrawString(100, 150, L"o‚Ä‚é", 0xffffff);
	fanShape_.Draw(this->GetOwner()->GetPosition());
}

const Vector2f FanCollider::AcutualPosition()
{
	return fanShape_.center + GetOwner()->GetPosition();
}

FanShape& FanCollider::GetFanShape()
{
	return fanShape_;
}

void FanCollider::SetIsAttack(bool isAttack)
{
	isAttack_ = isAttack;
}
