#include "CollisionManager.h"
#include "Collider.h"
#include <algorithm>
#include "Character.h"

void CollisionManager::Update()
{
	colliders_.remove_if([](std::shared_ptr<Collider>& c)
		{
			return  c->OwnerIsDead();
		});
	for (auto col : colliders_)
	{
		for (auto other : colliders_)
		{
			if (col == other)
			{
				continue;
			}
			if (col->IsHit(other))
			{
				CollisionInfo colInfo = { other };
				col->GetOwner()->OnHit(colInfo);
			}
		}
	}
	
}

void CollisionManager::AddCollider(Collider* collider)
{
	colliders_.emplace_back(collider);
}
