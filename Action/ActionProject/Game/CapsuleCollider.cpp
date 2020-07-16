#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider(std::shared_ptr<Character> owner, const char* tag)
	: Collider(owner, tag)
{
}
