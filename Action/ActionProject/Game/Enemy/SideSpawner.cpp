#include "SideSpawner.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "../CollisionManager.h"
#include "../CircleCollider.h"

SideSpawner::SideSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em, std::shared_ptr<CollisionManager>cm)
	: Spawner(pos, prototype, em), collisionManeger_(cm)
{
	frame_ = 0;
}


void SideSpawner::Update()
{
	static bool fromRight = false;
	++frame_;
	if (frame_ % (60 + rand() % 40 - 20) == 0)
	{
		auto enemy = Spawner::CreateClone();
		if (fromRight)
		{
			enemy->SetPosition({ -36, 500 });
		}
		else
		{
			enemy->SetPosition({ 836, 500 });
		}
		fromRight = !fromRight;
		enemyManager_->AddEnemy(enemy);
		collisionManeger_->AddCollider(new CircleCollider(enemyManager_->Enemies().back(), tagEnemyDamage, Circle({ 0, 0 }, 50)));
	}
}
