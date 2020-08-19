#include "Spawner.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "../Collision/CollisionManager.h"

Spawner::Spawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em, std::shared_ptr<CollisionManager> cm, std::shared_ptr<Camera>c):
	pos_(pos), 
	prototype_(prototype), 
	enemyManager_(em),
	collisionManeger_(cm),
	camera_(c)
{
}

Enemy* Spawner::CreateClone()
{
	return prototype_->MakeClone();
}
