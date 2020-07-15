#include "CircleCollider.h"
#include <assert.h>

CircleCollider::CircleCollider(std::shared_ptr<Character> owner, const char* tag)
	: Collider(owner, tag)
{
}

//CircleCollider::CircleCollider(const Circle& c) : circle_(c)
//{	
//}
//
//CircleCollider::CircleCollider(const Position2f& p, const float r) : circle_(p, r)
//{
//}

bool CircleCollider::IsHit(std::shared_ptr<Collider> col)
{
	assert(col != nullptr);
	CircleCollider* cCol = dynamic_cast<CircleCollider*>(&(*col));
	if (cCol == nullptr)
	{
		auto& other = cCol->circle_;
		auto sqDiff = (circle_.center - other.center).SQMagnitude();	// ãóó£ÇÃí∑Ç≥ÇÃ2èÊ
		auto totalRadius = circle_.radius + other.radius;	// îºåaÇÃçáåv
		return sqDiff <= totalRadius * totalRadius;
	}
	return false;
}
