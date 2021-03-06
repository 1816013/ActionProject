#include "BossSpawner.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CircleCollider.h"
#include "../Camera.h"

BossSpawner::BossSpawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<CollisionManager> collisionManager, std::shared_ptr<Camera> camera):
	Spawner(pos, prototype, enemyManager, collisionManager,camera),
	collisionManager_(collisionManager),
	updater_(&BossSpawner::SpawnUpdate)
{
}

void BossSpawner::Update()
{
	(this->*updater_)();
}

void BossSpawner::SpawnUpdate()
{
	auto rc = camera_->GetViewRange();
	if (pos_.x < rc.Left() || rc.Right() < pos_.x)return;
	auto clone = CreateClone();
	enemyManager_->AddEnemy(clone);
	const auto& circles = prototype_->GetCircles();
	const auto& c = circles[0];
	collisionManager_->AddCollider(new CircleCollider(enemyManager_->Enemies().back(), tagEnemyDamage, c));
	updater_ = &BossSpawner::SleepUpdate;
	
}

void BossSpawner::SleepUpdate()
{
}


