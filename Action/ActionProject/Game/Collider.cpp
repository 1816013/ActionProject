#include "Collider.h"
#include "Character.h"

Collider::Collider(std::shared_ptr<Character> owner, const char* tag):
	owner_(owner), tag_(tag)
{
}

bool Collider::OwnerIsDead()const
{
	return owner_.expired();
}

bool Collider::IsDeletable() const
{
	return isDeletable_;
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

const std::string& Collider::GetTag() const
{
	return tag_;
}

void Collider::Suside()
{
	isDeletable_ = true;
}
