#include "SideSpawner.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"
#include "../Camera.h"
#include <algorithm>

namespace
{
	constexpr int min_spawn_time = 40;
	constexpr int spawn_intarval = 40;
	constexpr float spawn_offset = 36;
}
SideSpawner::SideSpawner(const Position2f& pos, 
	Enemy* prototype, 
	std::shared_ptr<EnemyManager> em,
	std::shared_ptr<CollisionManager> cm,
	std::shared_ptr<Camera>c, 
	int averageSpawnFrame,
	int limitCnt,
	bool needBalance): 
	Spawner(pos, prototype, em, cm,  c)
{
	frame_ = 0;
	limitSpawnNum_ = limitCnt;
	averageSpawnFrame_ = averageSpawnFrame;
	needBalance_ = needBalance;
}


void SideSpawner::Update()
{
	auto viewRect = camera_->GetViewRange();
	if (pos_.x < viewRect.Left() || viewRect.Right() < pos_.x)return;
	static bool fromRight = false;
	++frame_;
	// ”­¶”§ŒÀ
	if (limitSpawnNum_ > 0)
	{
		regurators_.remove_if([](auto& reg) {return reg.ownedWeakRef.expired(); });
		if (regurators_.size() >= limitSpawnNum_)
		{
			return;
		}
	}
	auto variance = averageSpawnFrame_ / 3;
	if (frame_ % (/*60 + */rand() % averageSpawnFrame_ + rand() % (variance * 2) - variance + min_spawn_time) == 0)
	{
		auto enemy = Spawner::CreateClone();

		fromRight = !fromRight;

		if (needBalance_ && limitSpawnNum_ > 0)
		{
			fromRight = std::count_if(regurators_.begin(), regurators_.end(),
				[](auto& reg)
				{
					return reg.isRight;
				}) * 2 <= regurators_.size();
		}

		if (fromRight)
		{
			enemy->SetPosition({ viewRect.Left() + -spawn_offset  , 0.0f });
		}
		else
		{
			enemy->SetPosition({ viewRect.Right() + spawn_offset , 0.0f });
		}	
		enemyManager_->AddEnemy(enemy);

		// ŽãŽQÆ‚É’Ç‰Á
		if (limitSpawnNum_ > 0)
		{
			regurators_.emplace_back(enemyManager_->Enemies().back(), fromRight);
		}

		collisionManeger_->AddCollider(new CircleCollider(enemyManager_->Enemies().back(), tagEnemyDamage, Circle({ -18, -25 }, 50)));
	}
}
