#pragma once
#include <memory>
#include <list>


class Enemy;
using EnemyList = std::list<std::shared_ptr<Enemy>>;
/// <summary>
/// “G‚ğŠÇ—‚·‚é
/// </summary>
class EnemyManager
{
private:
	EnemyList enemies_;
public:
	void AddEnemy(Enemy* enemy);
	EnemyList& Enemies();
	void Update();
	void Draw();
};


