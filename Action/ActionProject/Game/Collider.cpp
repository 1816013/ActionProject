#include "Collider.h"
#include "Character.h"

bool Collider::OwnerIsDead()const
{
	return owner_.expired();
}

std::shared_ptr<Character> Collider::GetOwner()
{
	if (owner_.expired())
	{
		return nullptr;
	}
	else
	{
		return owner_.lock();
	}
}
