#include "SideSpawner.h"
#include "EnemyManager.h"
#include "Enemy.h"

SideSpawner::SideSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em)
	: Spawner(pos, prototype, em)
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
	}
}
