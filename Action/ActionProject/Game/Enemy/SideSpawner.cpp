#include "SideSpawner.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"
#include "../Camera.h"

namespace
{
	constexpr int min_spawn_time = 40;
	constexpr int spawn_intarval = 40;
	constexpr float spawn_offset = 36;
}
SideSpawner::SideSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera>c)
	: Spawner(pos, prototype, em, c), collisionManeger_(cm)
{
	frame_ = 0;
}


void SideSpawner::Update()
{
	static bool fromRight = false;
	++frame_;
	if (frame_ % (/*60 + */rand() % spawn_intarval + min_spawn_time) == 0)
	{
		auto enemy = Spawner::CreateClone();
		auto viewRect = camera_->GetViewRange();
		if (fromRight)
		{
			enemy->SetPosition({ viewRect.Left() + -spawn_offset  , 0.0f });
		}
		else
		{
			enemy->SetPosition({ viewRect.Right() + spawn_offset , 0.0f });
		}
		fromRight = !fromRight;
		enemyManager_->AddEnemy(enemy);
		collisionManeger_->AddCollider(new CircleCollider(enemyManager_->Enemies().back(), tagEnemyDamage, Circle({ -18, -25 }, 50)));
	}
}
