#include "SideSpawner.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "../CollisionManager.h"
#include "../CircleCollider.h"
#include "../../Camera.h"

SideSpawner::SideSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera>c)
	: Spawner(pos, prototype, em, c), collisionManeger_(cm)
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
		auto viewRect = camera_->GetViewRange();
		if (fromRight)
		{
			enemy->SetPosition({ viewRect.Left() + -36.0f  , 500.0f });
		}
		else
		{
			enemy->SetPosition({ viewRect.Right() + 36.0f , 500.0f });
		}
		fromRight = !fromRight;
		enemyManager_->AddEnemy(enemy);
		collisionManeger_->AddCollider(new CircleCollider(enemyManager_->Enemies().back(), tagEnemyDamage, Circle({ -18, -25 }, 50)));
	}
}
