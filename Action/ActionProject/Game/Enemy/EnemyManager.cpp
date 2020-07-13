#include "EnemyManager.h"
#include "Enemy.h"

void EnemyManager::AddEnemy(Enemy* e)
{
	enemies_.emplace_back(e);
}

void EnemyManager::Update()
{
	for (auto e : enemies_)
	{
		e->Update();
	}
	enemies_.remove_if([](std::shared_ptr<Enemy>& e) { return e->IsDeletable(); });
}

void EnemyManager::Draw()
{
	for (auto e : enemies_)
	{
		e->Draw();
	}
}
