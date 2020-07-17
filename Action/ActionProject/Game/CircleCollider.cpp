#include "CircleCollider.h"
#include <DxLib.h>
#include <assert.h>
#include "Character.h"

CircleCollider::CircleCollider(std::shared_ptr<Character> owner, const char* tag)
	: Collider(owner, tag)
{
}

CircleCollider::CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Circle& c) : Collider(owner, tag), circle_(c)
{	
}

CircleCollider::CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Position2f& p, const float r) : Collider(owner, tag), circle_(p, r)
{
}

bool CircleCollider::IsHit(std::shared_ptr<Collider> col)
{
	assert(col != nullptr);
	auto cCol = std::dynamic_pointer_cast<CircleCollider>(col);
	if (cCol != nullptr)
	{
		auto& other = cCol->circle_;
		Circle ownC(AcutualPosition(), circle_.radius);
		Circle otherC(cCol->AcutualPosition(), cCol->circle_.radius);
		
		auto sqDiff = (ownC.center - otherC.center).SQMagnitude();	// ãóó£ÇÃí∑Ç≥ÇÃ2èÊ
		auto totalRadius = ownC.radius + otherC.radius;	// îºåaÇÃçáåv
		return sqDiff <= totalRadius * totalRadius;
	}
	return false;
}

void CircleCollider::Draw()
{
#ifdef _DEBUG 
	if (OwnerIsDead())return;
	auto& pos = AcutualPosition() ;

	uint32_t col = 0xffffff;
	if (GetTag() == "pAtk") {
		col = 0xffaaaa;
	}

	DrawCircle(pos.x, pos.y,circle_.radius, col,0, 2);

	auto i = 0;
#endif 
}

const Circle& CircleCollider::GetCircle()const
{
	return circle_;
}

const Vector2f CircleCollider::AcutualPosition()
{
	return circle_.center + GetOwner()->GetPosition();
}
