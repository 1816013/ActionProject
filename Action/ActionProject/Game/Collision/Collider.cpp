#include "Collider.h"
#include "../Character.h"

Collider::Collider(std::shared_ptr<Character> owner, const char* tag, bool immortal):
	owner_(owner), tag_(tag), isImmortal_(immortal)
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
	if (!isImmortal_)
	{
		isDeletable_ = true;
	}
}

void Collider::Sleep()
{
	isActive_ = false;
}

void Collider::Awake()
{
	isActive_ = true;
}

bool Collider::IsAcrive()const
{
	return isActive_;
}
