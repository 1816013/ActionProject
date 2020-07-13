#include "EnemyManager.h"
#include "Enemy.h"

void EnemyManager::AddEnemy(Enemy* enemy)
{
	enemies_.emplace_back(enemy);
}

EnemyList& EnemyManager::Enemies()
{
	return enemies_;
}

void EnemyManager::Update()
{
	for (auto e : enemies_)
	{
		e->Update();
	}
	enemies_.remove_if([](std::shared_ptr<Enemy>& e) {
		return e->IsDeletable();
		});

}

void EnemyManager::Draw()
{
	for (auto e : enemies_)
	{
		e->Draw();
	}
}

