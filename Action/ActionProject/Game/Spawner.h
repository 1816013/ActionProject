#pragma once
#include <memory>
#include "../Geometry.h"
#include <list>

class Enemy;
class EnemyManager;
/// <summary>
/// ìGî≠ê∂äÌ
/// </summary>
class Spawner
{
protected:
	Position2f pos_;
	std::unique_ptr<Enemy> prototype_;
	std::shared_ptr<EnemyManager>& enemyManager_;
	//std::list<std::shared_ptr<Enemy>>& enemies_;

	virtual Enemy* CreateClone()final;
public:
	Spawner(const Position2f& pos, Enemy* prototype, std::shared_ptr<EnemyManager>& em
		/*,std::list<std::shared_ptr<Enemy>>& enemies*/);
	virtual ~Spawner() = default;
	//virtual std::shared_ptr<Enemy>* Spawn() = 0;
	virtual void Update() = 0;
};

