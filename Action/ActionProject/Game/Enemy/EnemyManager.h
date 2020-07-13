#pragma once
#include <memory>
#include <list>

class Enemy;
class EnemyManager
{
private:
	std::list<std::shared_ptr<Enemy>>enemies_;
public:
	//std::list<std::shared_ptr<Projectile>>& Projectiles();
	void AddEnemy(Enemy* p);
	void Update();
	void Draw();
};

