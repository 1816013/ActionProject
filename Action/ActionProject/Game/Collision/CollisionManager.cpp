#include "CollisionManager.h"
#include <DxLib.h>
#include "Collider.h"
#include <algorithm>
#include "../Character.h"
#include "../../Debug/Debugger.h"

namespace
{
	bool keyF1Pressed_ = false;
	bool debugDisp_ = false;
	std::pair<std::string, std::string> hitConbinationTable[] = { {tagEnemyDamage,tagPlayerAtack } };
}

void CollisionManager::Update()
{
	if (CheckHitKey(KEY_INPUT_F1))
	{
		if (!keyF1Pressed_)
		{
			debugDisp_ = !debugDisp_;
		}
		keyF1Pressed_ = true;
	}
	else
	{
		keyF1Pressed_ = false;
	}
	

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
				CollisionInfo colInfoOther = { other };
				col->GetOwner()->OnHit(colInfoOther);
				if (col->GetOwner()->IsActive())
				{
					col->Sleep();
				}
				else
				{
					col->Suside();
				}
				
				CollisionInfo colInfoOwn = { col };
				other->GetOwner()->OnHit(colInfoOwn);
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
