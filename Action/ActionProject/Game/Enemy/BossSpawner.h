#pragma once
#include "Spawner.h"
#include <memory>

class CollisionManager;
class BossSpawner : public Spawner
{
private:
	std::shared_ptr<CollisionManager>collisionManager_;

	using Updater_t = void (BossSpawner::*)();
	Updater_t updater_;

	void CreateUpdate();
	void SleepUpdate();
public:
	BossSpawner(const Position2f& pos,
		Enemy* prototype,
		std::shared_ptr<EnemyManager>enemyManager,
		std::shared_ptr<CollisionManager>collisionManager,
		std::shared_ptr<Camera> camera);
	~BossSpawner() = default;
	
	/// <summary>
	/// çXêV
	/// </summary>
	void Update()override;

};

