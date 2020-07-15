#pragma once
#include "Collider.h"
#include "../Geometry.h"
class CircleCollider : public Collider
{
private:
	Circle circle_;
public:
	CircleCollider(std::shared_ptr<Character> owner, const char* tag = "");

	///// <summary>
	///// ‰~î•ñ‚©‚ç‰~Õ“Ëî•ñ‚ğì‚é
	///// </summary>
	///// <param name="c">‰~î•ñ</param>
	//CircleCollider(const Circle& c);

	///// <summary>
	///// ’†SÀ•W‚Æ”¼Œaî•ñ‚©‚ç‰~Õ“Ëî•ñ‚ğì‚é
	///// </summary>
	///// <param name="c">’†SÀ•W</param>
	///// <param name="r">”¼Œa</param>
	//CircleCollider(const Position2f& p, const float r);
	bool IsHit(std::shared_ptr<Collider> col)override;
};

