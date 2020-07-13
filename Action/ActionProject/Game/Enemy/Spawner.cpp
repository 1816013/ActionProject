#include "Spawner.h"
#include "Enemy.h"
#include "EnemyManager.h"

Spawner::Spawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em/*, std::list<std::shared_ptr<Enemy>>& enemies*/):
	pos_(pos), 
	prototype_(prototype), 
	enemyManager_(em)/*, enemies_(enemies)*/
{
}

Enemy* Spawner::CreateClone()
{
	return prototype_->MakeClone();
}
