#include "CircleCollider.h"
#include <assert.h>

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(const Circle& c) : circle_(c)
{	
}

CircleCollider::CircleCollider(const Position2f& p, const float r) : circle_(p, r)
{
}

bool CircleCollider::IsHit(Collider* col)
{
	assert(col != nullptr);
	CircleCollider* cCol = dynamic_cast<CircleCollider*>(col);
	if (cCol == nullptr)
	{
		auto& other = cCol->circle_;
		auto sqDiff = (circle_.center - other.center).SQMagnitude();	// �����̒�����2��
		auto totalRadius = circle_.radius + other.radius;	// ���a�̍��v
		return sqDiff <= totalRadius * totalRadius;
	}
	return false;
}
