#include "CollisionManager.h"
#include <DxLib.h>
#include "Collider.h"
#include <algorithm>
#include "../Character.h"
#include "../../Debug/Debugger.h"

namespace
{
	std::pair<std::string, std::string> hitConbinationTable[] = { 
		{tagEnemyDamage,tagPlayerAtack }, 
		{tagEnemyBullet,tagPlayerDamage},
		{tagEnemyBullet,tagPlayerAtack },
		{tagPlayerDamage,tagEnemyAttack}
	};
}

void CollisionManager::Update()
{
	colliders_.remove_if([](std::shared_ptr<Collider>& c)
		{
			return  c->OwnerIsDead() || c->IsDeletable();
		});
	for (auto col : colliders_)
	{
		if (col->OwnerIsDead() || col->IsDeletable())
		{
			continue;
		}
		for (auto other : colliders_)
		{
			if(other->OwnerIsDead() || other->IsDeletable())
			{
				continue;
			}
			if (col == other)
			{
				continue;
			}
			auto cnt = std::count(begin(hitConbinationTable),
				end(hitConbinationTable),
				make_pair(col->GetTag(), other->GetTag()));
			if (cnt == 0)
			{
				continue;
			}
			if (col->IsHit(other) || other->IsHit(col))
			{
				CollisionInfo colInfoOwn = { col };
				CollisionInfo colInfoAnother = { other };
				col->GetOwner()->OnHit(colInfoOwn, colInfoAnother);
				if (col->GetOwner()->IsActive())
				{
					col->Sleep();
				}
				else
				{
					col->Suside();
				}
				
				other->GetOwner()->OnHit(colInfoAnother,colInfoOwn);
				if (other->GetOwner()->IsActive())
				{
					other->Sleep();
				}
				else
				{
					other->Suside();
				}
			}
		}
	}
	for (auto& col : colliders_) {
		if (col->IsDeletable() || col->OwnerIsDead())continue;
		col->Awake();
	}
}

void CollisionManager::DebugDraw(std::shared_ptr<Camera>c)
{
#ifdef _DEBUG
	if (!Debugger::Instance().IsDebugMode())
	{
		return;
	}
	for (auto col : colliders_)
	{
		col->Draw(c);
	}

	// 当たり判定情報を出力
	DrawFormatString(300, 30, 0xffffff, L"コライダー数 = %d", colliders_.size());
#endif // _DEBUG
}

void CollisionManager::AddCollider(Collider* collider)
{
	colliders_.emplace_back(collider);
}

std::list<std::shared_ptr<Collider>> CollisionManager::GetColliders()
{
	return colliders_;
}
