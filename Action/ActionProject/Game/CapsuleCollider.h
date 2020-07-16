#pragma once
#include "Collider.h"
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(std::shared_ptr<Character> owner, const char* tag = "");

	bool IsHit(std::shared_ptr<Collider> col)override;
	void Draw()override;
};

